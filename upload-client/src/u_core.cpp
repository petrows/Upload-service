#include "u_core.h"

#include "u_update.h"

#include "ui_askwindow.h"
#include "ui_zip_files.h"
#include "../3dpatry/qtsingleapplication/src/QtSingleApplication"
#include "u_common.h"

#include <QAction>
#include <QMenu>
#include <QDesktopServices>

void u_core_sleep::msleep(int ms)
{
	QThread::msleep(ms);
}

void __core_exit(int status = 0)
{
	exit(status);
}

u_core::u_core(QObject *parent) :
	QObject(parent)
{
	this->_ui_main = NULL;
	this->_ui_init = NULL;
	this->tray     = NULL;
	this->uploads_seed = 0;
	this->last_complete = NULL;
	this->last_complete_was = true;

	this->upd_has = false;

#ifdef Q_OS_LINUX
	this->os = "linux";
#endif
#ifdef Q_OS_WIN32
	this->os = "win";
#endif
#ifdef Q_OS_MAC
	this->os = "macx";
#endif
	// Get version from header file
	const int int_v[] = {VER_PRODUCTVERSION};
	this->version_s.sprintf("%d.%d.%d",int_v[0],int_v[1],int_v[2]);
	this->version_i[0] = int_v[0];
	this->version_i[1] = int_v[1];
	this->version_i[2] = int_v[2];

	this->build_tms = QString(__DATE__" "__TIME__);
}

u_core::~u_core()
{
	if (this->tray)
		delete this->tray;
	delete this->_ui_main;
}

void u_core::run ()
{
	// Start our app...
	core->reload_config();

	// First launch?
	if (!this->cfg.value("saved",false).toBool())
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Welcome");
		msgBox.setText(tr("This is first launch of u.petro.ws upload program."));
		msgBox.setInformativeText(tr("First time you must set-up you upload service Login & Password!"));
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();

		ui_settings * wnd = new ui_settings(this->_ui_main);
		wnd->exec();
	}
	// Okay, now we must do Global Init...
	this->start_new_sid();

	// Updating?
	if (QApplication::arguments().contains("--update-mode"))
	{
		u_update * upd = new u_update();
		upd->check_updates();
		return;
	}
	if (this->upd_has)
	{
		if (this->opt_upd_ask_period != -1 && (this->opt_upd_ask_period < (QDateTime::currentDateTime().toTime_t()-this->opt_upd_ask_last)))
		{
			this->cfg.setValue("update/last_ask",QDateTime::currentDateTime().toTime_t());
			int res = QMessageBox::question(0, tr("New version avaliable!"), tr("New version is avaliable, update program now?"),QMessageBox::Yes,QMessageBox::No);
			if (res == QMessageBox::Yes)
			{
				this->start_update();
				return;
			}
		}
	}

	this->tray = new QSystemTrayIcon(this);
	this->tray->setIcon(QIcon(":/icons/up"));
	this->tray->show();

	QMenu * tray_menu = new QMenu();

	this->tract_new_upload = new QAction(QIcon(":/icons/up"),tr("New upload..."),this);
	connect(this->tract_new_upload,SIGNAL(triggered()),SLOT(start_new_upload()));
	tray_menu->addAction(this->tract_new_upload);

	this->tract_show = new QAction(QIcon(":/icons/application-home"),tr("Show/Hide main window"),this);
	connect(this->tract_show,SIGNAL(triggered()),SLOT(toggle_main_wnd()));
	tray_menu->addAction(this->tract_show);

	this->tract_exit = new QAction(QIcon(":/icons/cross-button"),tr("Exit"),this);
	connect(this->tract_exit,SIGNAL(triggered()),SLOT(exit()));
	tray_menu->addAction(this->tract_exit);

	this->tray->setContextMenu(tray_menu);
	connect(this->tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),SLOT(tray_activate(QSystemTrayIcon::ActivationReason)));
	connect(this->tray,SIGNAL(messageClicked()),SLOT(tray_msg_click()));

	// Show main window?
	this->_ui_main = new ui_main();

	if (this->cfg.value("show_wnd",true).toBool())
	{
		this->_ui_main->show();
	}

	// Clean after update?
	if (QApplication::arguments().contains("--clean"))
	{
		QString old_dir = QApplication::arguments().at(QApplication::arguments().indexOf("--clean")+1);
		if (old_dir.length())
		{
			u_update::remove_dir(old_dir);
		}
	} else {
		// Get files??
		QStringList f_cmd;
		for (int x=1; x<QApplication::arguments().count(); x++)
		{
			f_cmd << QApplication::arguments().at(x);
		}
		if (f_cmd.count() > 0)
		{
			this->start_new_upload(f_cmd);
		}
	}
}

void u_core::start_update()
{
	u_update * upd = new u_update(this);
	upd->copy_to_tmp();
	upd->run_from_tmp();
	return;
}

void u_core::qsa_message(QString msg)
{
	// Okay, we have a message!
	if (msg == "exit")
	{
		QApplication::exit(0);
		return;
		this->exit();
	}
	if (msg == "show")
	{
		if (!this->_ui_main)
			this->_ui_main = new ui_main();
		this->_ui_main->show();
		this->_ui_main->activateWindow();
		return;
	}
	// Run new upload?
	QStringList files_in = msg.split("\n");
	this->start_new_upload(files_in);
}

void u_core::toggle_main_wnd()
{
	if (!this->_ui_main)
		this->_ui_main = new ui_main();

	if (this->_ui_main->isVisible())
	{
		// Hide...
		this->_ui_main->hide();
		this->cfg.setValue("show_wnd",false);
	} else {
		this->_ui_main->show();
		this->_ui_main->activateWindow();
		this->cfg.setValue("show_wnd",true);
	}
}

void u_core::tray_activate(QSystemTrayIcon::ActivationReason res)
{
	if (QSystemTrayIcon::Trigger == res)
	{
		this->toggle_main_wnd();
	}
}

void u_core::tray_msg_click()
{
	if (this->last_complete_was)
	{
		this->last_complete->show_form();
	}
}

void u_core::tmsg_copy_link()
{
	this->last_complete_was = false;
	if (!this->tray) return;
	this->tray->showMessage(tr("Copy links ok"),tr("There is a list of URL(s) in your clipboard now!"),QSystemTrayIcon::Information,1000);
}

void u_core::tmsg_complete(u_upload *upl)
{
	this->last_complete_was = true;
	this->last_complete = upl;
	if (!this->tray) return;
	if (upl->form && !upl->form->isActiveWindow())
		this->tray->showMessage(tr("Upload complete!"),tr("Upload #%1 is complete. Click this message to show it.").arg(upl->id));
}

void u_core::reload_config()
{
	this->login = this->cfg.value("login").toString();
	this->passw = this->cfg.value("passw").toString();

	this->opt_upd_ask_last   = this->cfg.value("update/last_ask",0).toInt();
	this->opt_upd_ask_period = this->cfg.value("update/ask_period",86400).toInt();
	this->opt_zip_files      = this->cfg.value("zip_files_mode",QChar('S')).toChar().toLatin1();
	this->tmp_folder         = this->cfg.value("tmp_folder",QDir::tempPath()).toString();

	this->opt_proxy_enable   = this->cfg.value("proxy/enable",false).toBool();
	this->opt_proxy_type     = this->cfg.value("proxy/type","").toString();
	this->opt_proxy_host     = this->cfg.value("proxy/host","").toString();
	this->opt_proxy_port     = this->cfg.value("proxy/port",0).toInt();
}

void u_core::reload_ui()
{
	if (this->_ui_main)
	{
		this->_ui_main->upd();
	}
}

void u_core::exit()
{
	if (this->has_uploading())
	{
		// int res = 0;
	}
	delete this->tray;
	this->tray = NULL;
	QtSingleApplication::exit(0);
	try {
		__core_exit(0);
	} catch (...) {}
}

bool u_core::has_uploading()
{
	for (int x=0; x<this->uploads.count(); x++)
	{
		if (this->uploads.at(x)->has_files_uploading())
			return true;
	}
	return false;
}

void u_core::start_new_sid()
{
	// 1. Show progress window...
	ui_init * progr = new ui_init();
	progr->show();

	// 2. Start reqest API
	u_api api;
	api.set_action("init");
	bool res = api.do_action();
	delete progr;

	if (!res)
	{
		// Api Error!
		QMessageBox msg;
		msg.setIcon(QMessageBox::Warning);
		msg.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
		msg.setWindowTitle(tr("Init error"));
		msg.setText(tr("An error was occured during program startup!"));
		msg.setInformativeText(api.last_error);

		int ret = msg.exec();

		if (ret == QMessageBox::Cancel)
		{
			this->exit();
			return;
		}
		if (ret == QMessageBox::Retry)
		{
			if (api.last_error_code == "LOGIN_ERROR")
			{
				// Show settings window...
				ui_settings * wnd = new ui_settings(this->_ui_main);
				wnd->exec();
			}
			this->start_new_sid();
			return;
		}
		return;
	}

	// Init OK!

	QDomElement uinfo = api.ans_dom.documentElement().firstChildElement("user");
	this->sid           = uinfo.firstChildElement("sid").childNodes().at(0).nodeValue();
	this->lk            = uinfo.firstChildElement("lk").childNodes().at(0).nodeValue();
	this->uploads_seed  = uinfo.firstChildElement("seed").childNodes().at(0).nodeValue().toInt();
	this->name          = uinfo.firstChildElement("name").childNodes().at(0).nodeValue();
	this->uid           = uinfo.firstChildElement("uid").childNodes().at(0).nodeValue().toInt();

	// New version?
	QDomElement updinfo = api.ans_dom.documentElement().firstChildElement("newversion");
	if (updinfo.attributes().namedItem("ver").nodeValue().length())
	{
		// New version!!
		this->upd_has = true;
		this->upd_v   = updinfo.attributes().namedItem("ver").nodeValue();
	}

	// TTL list
	QDomNodeList ttl_list = api.ans_dom.documentElement().firstChildElement("ttl").childNodes();
	for (int x=0; x<ttl_list.count(); x++)
	{
		if (ttl_list.at(x).nodeName() != "rec") continue;
		QDomElement ttl_el = ttl_list.at(x).toElement();
		this->ttls.append(qMakePair(ttl_el.attributes().namedItem("value").nodeValue().toInt(),ttl_el.attributes().namedItem("name").nodeValue()));
		if (ttl_el.attributes().namedItem("default").nodeValue() == "default")
			this->ttl_default = x;
	}

	// Files list...

	QDomNodeList u_list = api.ans_dom.documentElement().firstChildElement("uploads").childNodes();
	for (int x=0; x<u_list.count(); x++)
	{
		if (u_list.at(x).nodeName() != "upload") continue;
		QDomElement upload_el = u_list.at(x).toElement();

		u_upload * upl = new u_upload(this);
		upl->state = u_upload::Uploaded;
		upl->id    = upload_el.attributes().namedItem("id").nodeValue().toInt();
		upl->ttl   = upload_el.attributes().namedItem("ttl").nodeValue().toInt();
		upl->code  = upload_el.attributes().namedItem("code").nodeValue();
		upl->ph    = upload_el.attributes().namedItem("ph").nodeValue();
		upl->title = upload_el.attributes().namedItem("comment").nodeValue();
		upl->prolong    = upload_el.attributes().namedItem("prolong").nodeValue().toInt() == 1;
		upl->tm_created = QDateTime::fromTime_t(upload_el.attributes().namedItem("tms_upload").nodeValue().toInt());
		upl->tm_delete  = QDateTime::fromTime_t(upload_el.attributes().namedItem("tms_delete").nodeValue().toInt());
		upl->tm_last    = QDateTime::fromTime_t(upload_el.attributes().namedItem("tms_last").nodeValue().toInt());

		// File list
		QDomNodeList f_list = upload_el.firstChildElement("files").childNodes();
		for (int f=0; f<f_list.count(); f++)
		{
			u_upload_file * fl = new u_upload_file(upl);
			fl->state = u_upload_file::Uploaded;
			fl->file_n    = f_list.at(f).attributes().namedItem("n").nodeValue().toInt();
			fl->file_dh   = f_list.at(f).attributes().namedItem("dh").nodeValue();
			fl->file_name = f_list.at(f).attributes().namedItem("name").nodeValue();
			fl->file_size = f_list.at(f).attributes().namedItem("size").nodeValue().toLongLong();
			fl->file_size_uploaded = fl->file_size;
			upl->add_file_itm(fl);
		}
		upl->recount();
		this->uploads.append(upl);
	}

	return;
}

bool u_core::sid_ready()
{
	return !this->sid.isEmpty();
}

void u_core::start_new_upload(QStringList lst)
{
	// Get files...
	if (lst.isEmpty())
	{
		QFileDialog dlg;
		dlg.setFileMode(QFileDialog::ExistingFiles);
		dlg.setViewMode(QFileDialog::Detail);

		if (!dlg.exec())
			return; // No files

		lst = dlg.selectedFiles();
	}

	if (!lst.count())
		return;

	QFileInfo in_i(lst.at(0));
	bool remove_after_upload = false;
	if ((in_i.isDir() || lst.count() > 1) && this->opt_zip_files != 'N')
	{
		bool is_agree_pack = true;
		if (this->opt_zip_files == 'S')
		{
			int res = QMessageBox::question(0, tr("Send as archive?"),tr("Seems to be that you have added more than file(s) or folder(s). Compress them to ZIP archive before sending?"),QMessageBox::Yes,QMessageBox::No);
			is_agree_pack = (res == QMessageBox::Yes);
		}
		if (is_agree_pack)
		{
			ui_zip_files * zip_wnd = new ui_zip_files();
			zip_wnd->show();
			if (!zip_wnd->start_files(lst))
				return;
			lst.clear();
			lst << zip_wnd->zip_out;
			remove_after_upload = true;
		}
	}

	QStringList lst_out;

	for (int x=0; x<lst.count(); x++)
	{
		lst_out.append(this->_scan_upl_folders(lst.at(x)));
	}

	lst_out.removeDuplicates();
	if (!lst_out.count())
		return;

	// qDebug() << lst_out;

	u_upload * upl = new u_upload(this);
	upl->state = u_upload::Uploading;
	upl->remove_after_upload = remove_after_upload;
	upl->show_form();
	for (int x=0; x<lst_out.count(); x++)
	{
		if (!upl->start_file(lst_out[x]))
		{
			qDebug() << "Start error!!!";
		}
		QApplication::processEvents();
	}
	this->uploads.append(upl);
	upl->status_recheck();
	// qDebug() << "All count: " << this->uploads.count();
	qDebug() << "Added: " << upl->get_title();
	this->reload_ui();
}

QStringList u_core::_scan_upl_folders(QString fname)
{
	QStringList out;
	QFileInfo finf(fname);
	if (finf.isDir())
	{
		// It is a dir...
		QDir dr(fname);
		QStringList dr_data = dr.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
		for (int x=0; x<dr_data.count(); x++)
		{
			out.append(this->_scan_upl_folders(fname + "/" + dr_data.at(x)));
		}
	} else {
		// File?
		if (finf.isReadable())
		{
			out << finf.absoluteFilePath();
		}
	}
	return out;
}

QString u_core::format_size(qint64 sz)
{
	QString pt;
	float   out = 0.0f;

	if (sz < 1024)
	{
		pt  = tr("b");
		out = sz;
	} else if (sz < 1024*1024) {
		pt  = tr("Kb");
		out = (long double)sz/(long double)(1024);
	} else if (sz < 1024*1024*1024) {
		pt  = tr("Mb");
		out = (long double)sz/(long double)(1024*1024);
	} else {
		pt  = tr("Gb");
		out = (long double)sz/(long double)(1024*1024*1024);
	}

	return QString().sprintf("%.2f ",out) + pt;
}

QString u_core::str_md5(QString in)
{
	MD5 context;
	context.update ((unsigned char*)in.toStdString().c_str(), in.length());
	context.finalize ();
	return context.hex_digest();
}

void u_core::open_link(QString url)
{
	QDesktopServices url_handler;
	url_handler.openUrl(url);
}
