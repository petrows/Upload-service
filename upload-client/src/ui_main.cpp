#include "ui_main.h"
#include "ui_ui_main.h"

#include "ui_about.h"

#include <QClipboard>
#include <QCloseEvent>
#include <QMimeData>

ui_main::ui_main(QWidget *parent) : QMainWindow(parent), ui(new Ui::ui_main) {
	this->setWindowIcon(QIcon(":/icons/db_commit.ico"));

	ui->setupUi(this);
	this->ulist = new ui_wdg_ulist(this);
	this->ui->layoutList->addWidget(this->ulist);
	this->ulist->show();

	this->setWindowTitle("U.petro.ws : " + core->name);

	// Has updates?
	if (core->upd_has) {
		// Has updates!
		this->ui->actionUpdatesMenu->setText(tr("New version avaliable!"));
		QFont mfont = this->ui->actionUpdatesMenu->font();
		mfont.setBold(true);
		this->ui->actionUpdatesMenu->setFont(mfont);
		connect(this->ui->actionUpdatesMenu, SIGNAL(triggered()), core, SLOT(start_update()));
	} else {
		this->ui->actionUpdatesMenu->setText(tr("You are using latest version."));
		this->ui->actionUpdatesMenu->setDisabled(true);
	}
	connect(this->ui->actionUpdatesMenu, SIGNAL(triggered()), core, SLOT(start_update()));
}

ui_main::~ui_main() { delete ui; }

void ui_main::closeEvent(QCloseEvent *ev) {
	this->hide();
	ev->ignore();
}

void ui_main::dragEnterEvent(QDragEnterEvent *ev) {
	if (ev->mimeData()->hasUrls())
		ev->acceptProposedAction();
}

void ui_main::dropEvent(QDropEvent *ev) {
	QStringList ulist;
	for (int x = 0; x < ev->mimeData()->urls().count(); x++)
		ulist.append(ev->mimeData()->urls().at(x).toLocalFile());
	// qDebug() << ulist;
	core->start_new_upload(ulist);
}

void ui_main::upd() { this->ulist->upd(); }

void ui_main::on_actionHide_triggered() { this->hide(); }

void ui_main::on_actionExit_triggered() { core->exit(); }

void ui_main::on_actionNew_upload_triggered() { core->start_new_upload(); }

void ui_main::on_actionSettings_triggered() {
	ui_settings *wnd = new ui_settings(this);
	wnd->show();
}

void ui_main::on_btnNewUpload_clicked() { this->on_actionNew_upload_triggered(); }

void ui_main::on_actionAbout_program_triggered() {
	// Show 'About' window...
	ui_about *wnd = new ui_about(this);
	wnd->show();
}

void ui_main::on_actionHome_page_triggered() { core->open_link("http://" UPLOAD_DOMAIN "/page/client/"); }

void ui_main::on_actionAbout_Qt_triggered() { QApplication::aboutQt(); }

void ui_main::on_btnClipUpload_clicked() {
	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();

	if (mimeData->hasImage()) {
		// setPixmap();
		qDebug() << "Upload image!";

		QPixmap pix = qvariant_cast<QPixmap>(mimeData->imageData());

		QFile file(QDir::tempPath() + "/pasted-image.png");
		file.open(QIODevice::WriteOnly);
		pix.save(&file, "PNG");

		QStringList ulist;
		ulist.append(file.fileName());
		core->start_new_upload(ulist);

	} else if (mimeData->hasHtml()) {
		qDebug() << "Upload html!";
	} else if (mimeData->hasText()) {
		// Check - this is a URL?
		if (mimeData->urls().count()) {
			qDebug() << "Upload file URL!";

			QStringList ulist;
			for (int x = 0; x < mimeData->urls().count(); x++) {
				QString localFile = mimeData->urls().at(x).toLocalFile();
				if (QFile(localFile).exists()) {
					qDebug() << "File: " << mimeData->urls().at(x);
					ulist.append(mimeData->urls().at(x).toLocalFile());
				}
			}

			if (ulist.size()) {
				core->start_new_upload(ulist);

				return;
			}
		}

		qDebug() << "Upload text!";
	} else {
		qDebug() << "No clip!";
	}
}
