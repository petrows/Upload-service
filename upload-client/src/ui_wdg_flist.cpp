#include "ui_wdg_flist.h"
#include "ui_wdg_btnlabel.h"
#include <QAction>
#include <QClipboard>

ui_wdg_flist::ui_wdg_flist(QWidget *parent, u_upload * upl) :
	QTreeView(parent)
{
	this->upl = upl;
	mdl = new ui_wdg_flist_mdl();
	mdl->upl = upl;
	this->setModel(mdl);
	this->setAlternatingRowColors(true);
	this->setAllColumnsShowFocus(false);
	this->setContextMenuPolicy(Qt::ActionsContextMenu);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);

	ui_wdg_flist_control * cntrl = new ui_wdg_flist_control();
	this->setItemDelegateForColumn(3,cntrl);

	this->cm_copyUrl = new QAction(QIcon(QIcon(":/icons/clipboard-p")),tr("Copy file link (s)"),this);
	connect(this->cm_copyUrl,SIGNAL(triggered()),SLOT(son_cm_copyLink()));
	this->addAction(this->cm_copyUrl);
	this->cm_copyUrlDesc = new QAction(QIcon(QIcon(":/icons/clipboard-p-doc")),tr("Copy file link (s) + Description"),this);
	connect(this->cm_copyUrlDesc,SIGNAL(triggered()),SLOT(son_cm_copyLinkDesc()));
	this->addAction(this->cm_copyUrlDesc);
	this->cm_openUrl = new QAction(QIcon(":/icons/application-browser"),tr("Open file link (s)"),this);
	connect(this->cm_openUrl,SIGNAL(triggered()),SLOT(son_cm_openLink()));
	this->addAction(this->cm_openUrl);

	this->upd();
}
void ui_wdg_flist::resizeEvent(QResizeEvent */*event*/)
{
	this->setColumnWidth(0, 20);
	this->setColumnWidth(1, this->size().width() - 300);
	this->setColumnWidth(2, 100);
	this->setColumnWidth(3, 150);
}
void ui_wdg_flist::upd()
{
	this->mdl->upd();

	QModelIndex root = this->rootIndex();

	for (int x=0; x<this->model()->rowCount(root); x++)
	{
		this->openPersistentEditor(this->model()->index(x,3,root));
	}
}

void ui_wdg_flist::son_dblclick(QModelIndex index)
{
	// Open info window
	u_upload * upl = static_cast<u_upload*>(index.internalPointer());
	upl->show_form();
}

void ui_wdg_flist::son_cm_copyLink()
{
	QList<u_upload_file*> f_was;
	QModelIndexList sel = this->selectedIndexes();
	QStringList out;
	for (int x=0; x<sel.count(); x++)
	{
		u_upload_file * f = static_cast<u_upload_file*>(sel.at(x).internalPointer());
		if (f_was.contains(f)) continue;
		f_was.append(f);
		out << f->file_link();
	}

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(out.join("\n"));
}
void ui_wdg_flist::son_cm_copyLinkDesc()
{
	QList<u_upload_file*> f_was;
	QModelIndexList sel = this->selectedIndexes();
	QStringList out;
	for (int x=0; x<sel.count(); x++)
	{
		u_upload_file * f = static_cast<u_upload_file*>(sel.at(x).internalPointer());
		if (f_was.contains(f)) continue;
		f_was.append(f);
		out << f->file_name + " (" + u_core::format_size(f->file_size) + ")" + " : " +f->file_link();
	}

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(out.join("\n"));
}

void ui_wdg_flist::son_cm_openLink()
{
	QList<u_upload_file*> f_was;
	QModelIndexList sel = this->selectedIndexes();

	for (int x=0; x<sel.count(); x++)
	{
		u_upload_file * f = static_cast<u_upload_file*>(sel.at(x).internalPointer());
		if (f_was.contains(f)) continue;
		f_was.append(f);
		core->open_link(f->file_link());
	}
}

// --------------------------------------------------------------------------------------

ui_wdg_flist_control::ui_wdg_flist_control(QObject *parent) :
	QItemDelegate(parent)
{

}

void ui_wdg_flist_control::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(painter)
	Q_UNUSED(option)
	Q_UNUSED(index)
	// No paint, just editor...
#ifdef Q_OS_LINUX
	QItemDelegate::paint(painter,option,index);
#endif
}

QWidget * ui_wdg_flist_control::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
	// Get upload item
	u_upload_file * upl = static_cast<u_upload_file*>(index.internalPointer());
	if (!upl)
		return NULL; // WTF?

	QWidget * root_widget = new QWidget(parent);
	QHBoxLayout * layout = new QHBoxLayout(root_widget);
	layout->setContentsMargins(3,0,3,0);
	layout->setSpacing(3);

	QSpacerItem * sp;

	if (upl->state == u_upload_file::Uploading)
	{
		// Draw progress widget
		if (upl->progr_flist != NULL)
		{
			QProgressBar * old_bar = upl->progr_flist;
			upl->progr_flist = NULL;
			old_bar->blockSignals(true); // Do NOT send 'destroed' cry...
			delete old_bar;
		}

		upl->progr_flist = new QProgressBar(root_widget);
		layout->addWidget(upl->progr_flist);

		connect(upl->progr_flist,SIGNAL(destroyed()),upl,SLOT(flist_progr_del()));
		upl->progr_flist->setValue(upl->file_progress());
		upl->progr_flist->setMaximumHeight(20);
		upl->progr_flist->show();
	}
	if (upl->state == u_upload_file::Uploaded)
	{
		layout->setContentsMargins(10,0,0,0);

		QLabel * lbl;
		lbl = new QLabel(root_widget);
		lbl->setPixmap(QIcon(":/icons/tick").pixmap(QSize(16,16)));
		layout->addWidget(lbl);
		lbl = new QLabel(root_widget);
		lbl->setText("<span style='color:green'>"+tr("Uploaded")+":</span>");
		layout->addWidget(lbl);

		ui_wdg_btnlabel * btn;

		btn = new ui_wdg_btnlabel(root_widget);
		btn->setPixmap(QIcon(":/icons/doc-attr-l").pixmap(QSize(16,16)));
		btn->setToolTip(tr("Copy download link - open file in browser 'as is'"));
		connect(btn,SIGNAL(clicked()),upl,SLOT(copy_file_link()));
		layout->addWidget(btn);

		btn = new ui_wdg_btnlabel(root_widget);
		btn->setPixmap(QIcon(":/icons/doc-attr-f").pixmap(QSize(16,16)));
		btn->setToolTip(tr("Copy download (forced) link - force broswer to save file"));
		connect(btn,SIGNAL(clicked()),upl,SLOT(copy_file_link()));
		layout->addWidget(btn);

		sp = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		layout->addItem(sp);
	}
	return root_widget;
}

// --------------------------------------------------------------------------------------

ui_wdg_flist_mdl::ui_wdg_flist_mdl(QObject */*parent*/)
{
}
ui_wdg_flist_mdl::~ui_wdg_flist_mdl()
{
}
QModelIndex ui_wdg_flist_mdl::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();
	if (parent.isValid())
		return QModelIndex(); // No tree

	return createIndex(row, column, this->upl->files.at(row));
}

QModelIndex ui_wdg_flist_mdl::parent(const QModelIndex &/*index*/) const
{
	return QModelIndex();
}
int ui_wdg_flist_mdl::rowCount(const QModelIndex &parent) const
{
	if (!parent.isValid())
		return this->upl->files.count();
	return 0;
}
int ui_wdg_flist_mdl::columnCount(const QModelIndex &/*parent*/) const
{
	return 4;
}
QVariant ui_wdg_flist_mdl::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal)
		return QVariant();
	if (Qt::DisplayRole == role)
	{
		if (section == 0)
			return tr("#");
		if (section == 1)
			return tr("Name");
		if (section == 2)
			return tr("Size");
		if (section == 3)
			return tr("Status");
	}
	return QVariant();
}
QVariant ui_wdg_flist_mdl::data(const QModelIndex &index, int role) const
{
	u_upload_file * upl_itm = static_cast<u_upload_file*>(index.internalPointer());
	if (!upl_itm)
		return QVariant();

	// QMutexLocker lock(&upl_itm->mtx_info);

	if (Qt::DisplayRole == role)
	{
		if (index.column() == 0)
			return QString::number(index.row()+1);
		if (index.column() == 1)
			return upl_itm->file_name;
		if (index.column() == 2)
			return u_core::format_size(upl_itm->file_size);
		if (index.column() == 3)
		{
			// Status...
			return QVariant();
		}
		return "";
	}
	if (Qt::TextAlignmentRole == role)
	{
		if (index.column() == 2)
			return QVariant(Qt::AlignVCenter|Qt::AlignRight);
	}
	if (Qt::DecorationRole == role)
	{
		if (index.column() == 1)
			return QApplication::style()->standardIcon(QStyle::SP_FileLinkIcon);
	}
	if (Qt::SizeHintRole == role)
	{
		return QSize(100,25);
	}
	return QVariant();
}
void ui_wdg_flist_mdl::upd()
{
	beginResetModel();
	endResetModel();
}
Qt::ItemFlags ui_wdg_flist_mdl::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}

