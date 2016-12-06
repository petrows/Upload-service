#include "ui_wdg_ulist.h"
#include "ui_wdg_btnlabel.h"
#include <QAction>
#include <QClipboard>

ui_wdg_ulist::ui_wdg_ulist(QWidget *parent) : QTreeView(parent) {
	mdl = new ui_wdg_ulist_mdl();
	this->setModel(mdl);
	this->setAlternatingRowColors(true);
	this->setAllColumnsShowFocus(false);
	this->setRootIsDecorated(false);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);

	this->cm_viewInfo = new QAction(QIcon(":/icons/folder-open-doc"), tr("View upload info"), this);
	connect(this->cm_viewInfo, SIGNAL(triggered()), SLOT(open_info()));
	this->addAction(this->cm_viewInfo);

	QAction *act_title = new QAction(this);
	act_title->setDisabled(true);
	act_title->setText(tr("Copy to clipboard:"));
	this->addAction(act_title);

	this->cm_copyUrl = new QAction(QIcon(":/icons/clipboard-list"), tr("Copy upload page URL(s)"), this);
	connect(this->cm_copyUrl, SIGNAL(triggered()), SLOT(copy_links()));
	this->addAction(this->cm_copyUrl);
	this->cm_copyAllFilesUrl = new QAction(QIcon(":/icons/clipboard-p"), tr("Copy All files URL(s)"), this);
	connect(this->cm_copyAllFilesUrl, SIGNAL(triggered()), SLOT(copy_all_files_links()));
	this->addAction(this->cm_copyAllFilesUrl);
	this->cm_copyAllFilesUrlDescr = new QAction(QIcon(":/icons/clipboard-p-doc"), tr("Copy All files URL(s) + Description"), this);
	connect(this->cm_copyAllFilesUrlDescr, SIGNAL(triggered()), SLOT(copy_all_files_links_descr()));
	this->addAction(this->cm_copyAllFilesUrlDescr);

	ui_wdg_ulist_control *cntrl = new ui_wdg_ulist_control();
	this->setItemDelegateForColumn(2, cntrl);

	connect(this, SIGNAL(doubleClicked(QModelIndex)), SLOT(son_dblclick(QModelIndex)));

	this->upd();
}
void ui_wdg_ulist::resizeEvent(QResizeEvent * /*event*/) {
	this->setColumnWidth(0, this->size().width() - 300);
	this->setColumnWidth(1, 100);
	this->setColumnWidth(2, 180);
}
void ui_wdg_ulist::upd() {
	this->mdl->upd();
	this->reset();

	QModelIndex root = this->rootIndex();

	// qDebug() << this->model()->rowCount(root);

	for (int x = 0; x < this->model()->rowCount(root); x++) {
		// We really do not do this here...
		// in Editor Delegeate it will be better
		this->openPersistentEditor(this->model()->index(x, 2, root));
	}
	// emit this->rowsRemoved(QModelIndex(),0,0);
	this->rowsInserted(root, 0, this->model()->rowCount(root) - 1);
}

void ui_wdg_ulist::son_dblclick(QModelIndex index) {
	// Open info window
	u_upload *upl = static_cast<u_upload *>(index.internalPointer());
	upl->show_form();
}

void ui_wdg_ulist::copy_links() {
	QStringList urls;
	QList<u_upload *> u_was;

	QModelIndexList ind = this->selectedIndexes();
	for (int x = 0; x < ind.count(); x++) {
		u_upload *upl = static_cast<u_upload *>(ind.at(x).internalPointer());
		if (u_was.contains(upl))
			continue;
		u_was.append(upl);
		urls << upl->public_link();
	}
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(urls.join("\n"));
}

void ui_wdg_ulist::copy_all_files_links() {
	QStringList urls;
	QList<u_upload *> u_was;

	QModelIndexList ind = this->selectedIndexes();
	for (int x = 0; x < ind.count(); x++) {
		u_upload *upl = static_cast<u_upload *>(ind.at(x).internalPointer());
		if (u_was.contains(upl))
			continue;
		u_was.append(upl);

		for (int f = 0; f < upl->files.count(); f++) {
			if (upl->files.at(f)->state == u_upload_file::Uploaded) {
				urls << upl->files.at(f)->file_link();
			}
		}
	}
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(urls.join("\n"));
}

void ui_wdg_ulist::copy_all_files_links_descr() {
	QStringList urls;
	QList<u_upload *> u_was;

	QModelIndexList ind = this->selectedIndexes();
	for (int x = 0; x < ind.count(); x++) {
		u_upload *upl = static_cast<u_upload *>(ind.at(x).internalPointer());
		if (u_was.contains(upl))
			continue;
		u_was.append(upl);

		for (int f = 0; f < upl->files.count(); f++) {
			if (upl->files.at(f)->state == u_upload_file::Uploaded) {
				urls << upl->files.at(f)->file_name + " (" + u_core::format_size(upl->files.at(f)->file_size) + ") : " + upl->files.at(f)->file_link();
			}
		}
	}
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(urls.join("\n"));
}

void ui_wdg_ulist::open_info() {
	QList<u_upload *> u_was;

	QModelIndexList ind = this->selectedIndexes();
	for (int x = 0; x < ind.count(); x++) {
		u_upload *upl = static_cast<u_upload *>(ind.at(x).internalPointer());
		if (u_was.contains(upl))
			continue;
		u_was.append(upl);
		upl->show_form();
	}
}

// --------------------------------------------------------------------------------------

ui_wdg_ulist_control::ui_wdg_ulist_control(QObject *parent) : QItemDelegate(parent) {}

void ui_wdg_ulist_control::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	Q_UNUSED(painter)
	Q_UNUSED(option)
	Q_UNUSED(index)
// No paint, just editor...
#ifdef Q_OS_LINUX
	QItemDelegate::paint(painter, option, index);
#endif
}

QWidget *ui_wdg_ulist_control::createEditor(QWidget *parent, const QStyleOptionViewItem & /*option*/, const QModelIndex &index) const {
	// Get upload item
	u_upload *upl = static_cast<u_upload *>(index.internalPointer());
	if (!upl)
		return NULL; // WTF?

	QWidget *root_widget = new QWidget(parent);
	QHBoxLayout *layout = new QHBoxLayout(root_widget);
	layout->setContentsMargins(3, 0, 3, 0);
	layout->setSpacing(3);

	QSpacerItem *sp;

	if (upl->state == u_upload::Uploading) {
		// Draw progress widget
		if (upl->progr_ulist != NULL) {
			QProgressBar *old_bar = upl->progr_ulist;
			upl->progr_ulist = NULL;
			old_bar->blockSignals(true); // Do NOT send 'destroed' cry...
			delete old_bar;
		}

		upl->progr_ulist = new QProgressBar(root_widget);
		layout->addWidget(upl->progr_ulist);

		connect(upl->progr_ulist, SIGNAL(destroyed()), upl, SLOT(ulist_progr_del()));
		upl->progr_ulist->setValue(upl->total_progress());
		upl->progr_ulist->setMaximumHeight(20);
		upl->progr_ulist->show();
	}
	if (upl->state == u_upload::Uploaded) {
		layout->setContentsMargins(10, 0, 10, 0);

		QLabel *lbl;
		lbl = new QLabel(root_widget);
		lbl->setPixmap(QIcon(":/icons/tick").pixmap(QSize(16, 16)));
		layout->addWidget(lbl);
		lbl = new QLabel(root_widget);
		lbl->setText("&nbsp;<span style='color:gray;'>" + tr("To") + " </span><span style='color:" + upl->ttl_color() + ";'>" + upl->ttl_date() + "</span>");
		lbl->setToolTip(upl->ttl_period());
		layout->addWidget(lbl);

		sp = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
		layout->addItem(sp);

		ui_wdg_btnlabel *btn;

		btn = new ui_wdg_btnlabel(root_widget);
		btn->setPixmap(QIcon(":/icons/folder-open-doc").pixmap(QSize(16, 16)));
		btn->setToolTip(tr("View info"));
		connect(btn, SIGNAL(clicked()), upl, SLOT(show_form()));
		layout->addWidget(btn);

		btn = new ui_wdg_btnlabel(root_widget);
		btn->setPixmap(QIcon(":/icons/clipboard-list").pixmap(QSize(16, 16)));
		btn->setToolTip(tr("Copy public link"));
		connect(btn, SIGNAL(clicked()), upl, SLOT(copy_upload_link()));
		layout->addWidget(btn);
	}
	if (upl->state == u_upload::Error) {
		sp = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
		layout->addItem(sp);
		QLabel *lbl = new QLabel(root_widget);
		lbl->setText("<span style='font-weight:bold;color:red;'>" + tr("Upload error") + "</span>");
		layout->addWidget(lbl);
		sp = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
		layout->addItem(sp);
	}
	if (upl->state == u_upload::Idle) {
		sp = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
		layout->addItem(sp);
		QLabel *lbl = new QLabel(root_widget);
		lbl->setText("<span style='color:gray;'>" + tr("Unknown") + "</span>");
		layout->addWidget(lbl);
		sp = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
		layout->addItem(sp);
	}
	return root_widget;
}

// --------------------------------------------------------------------------------------

ui_wdg_ulist_mdl::ui_wdg_ulist_mdl(QObject * /*parent*/) {}
ui_wdg_ulist_mdl::~ui_wdg_ulist_mdl() {}
QModelIndex ui_wdg_ulist_mdl::index(int row, int column, const QModelIndex &parent) const {
	if (!hasIndex(row, column, parent))
		return QModelIndex();
	if (parent.isValid())
		return QModelIndex(); // No tree

	return createIndex(row, column, core->uploads.at(row));
}

QModelIndex ui_wdg_ulist_mdl::parent(const QModelIndex & /*index*/) const { return QModelIndex(); }
int ui_wdg_ulist_mdl::rowCount(const QModelIndex &parent) const {
	if (!parent.isValid())
		return core->uploads.count();
	return 0;
}
int ui_wdg_ulist_mdl::columnCount(const QModelIndex & /*parent*/) const { return 3; }
QVariant ui_wdg_ulist_mdl::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation != Qt::Horizontal)
		return QVariant();
	if (Qt::DisplayRole == role) {
		if (section == 0)
			return tr("Name/Files");
		if (section == 1)
			return tr("Size");
		if (section == 2)
			return tr("Status");
	}
	return QVariant();
}
QVariant ui_wdg_ulist_mdl::data(const QModelIndex &index, int role) const {
	u_upload *upl_itm = static_cast<u_upload *>(index.internalPointer());
	if (!upl_itm)
		return QVariant();

	// QMutexLocker lock(&upl_itm->mtx_info);

	if (Qt::DisplayRole == role) {
		if (index.column() == 0)
			return upl_itm->get_title();
		if (index.column() == 1)
			return u_core::format_size(upl_itm->size_total);
		if (index.column() == 2) {
			// Status...
			return QVariant();
		}
		return "";
	}
	if (Qt::TextAlignmentRole == role) {
		if (index.column() == 1)
			return QVariant(Qt::AlignVCenter | Qt::AlignRight);
	}
	if (Qt::DecorationRole == role) {
		if (index.column() == 0)
			return QIcon(":/icons/notebook-share");
	}
	if (Qt::SizeHintRole == role) {
		return QSize(100, 25);
	}
	return QVariant();
}
void ui_wdg_ulist_mdl::upd() {
	beginResetModel();
	endResetModel();
	// qDebug() << "Reset model! (ulist)";
}
Qt::ItemFlags ui_wdg_ulist_mdl::flags(const QModelIndex &index) const {
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}
