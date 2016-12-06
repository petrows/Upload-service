#include "u_update.h"
#include "u_api.h"
#include "ui_ui_update.h"
#include "ui_update.h"

#include <QCryptographicHash>
#include <QProcess>

#ifdef Q_OS_LINUX
#include <sys/stat.h>
#endif
#ifdef Q_OS_MAC
#include <sys/stat.h>
#endif

u_update::u_update(QObject *parent) : QObject(parent) {
	this->ui = new ui_update();
	this->ui->upd = this;
	this->ui->init();

	this->size_total = 0;
	this->size_downloaded = 0;

	this->mng = new QNetworkAccessManager(this);
	connect(this->mng, SIGNAL(finished(QNetworkReply *)), SLOT(_down_done(QNetworkReply *)));

// Scan my files & folders
#ifdef Q_OS_LINUX
	// One file - binary
	this->orig_dir = QCoreApplication::applicationDirPath() + "";
	QFileInfo bininf(QCoreApplication::applicationFilePath());
	this->orig_dir_in = "/" + bininf.fileName();
	this->orig_dir_in = "/";
	this->orig_exe = bininf.fileName();
#endif
#ifdef Q_OS_WIN32
	// Our home-path is root
	this->orig_dir = QCoreApplication::applicationDirPath() + "";
	QFileInfo bininf(QCoreApplication::applicationFilePath());
	this->orig_dir_in = "/";
	this->orig_exe = bininf.fileName();
	qDebug() << this->orig_exe;
#endif
#ifdef Q_OS_MAC
	// Our home-path is root/../../
	QDir app_path = QDir(QCoreApplication::applicationDirPath());
	app_path.cd("..");
	app_path.cd("..");
	this->orig_dir = app_path.absoluteFilePath(app_path.path());
	this->orig_dir_in = "/";
	this->orig_exe = app_path.relativeFilePath(QCoreApplication::applicationFilePath());
	qDebug() << this->orig_dir;
	qDebug() << this->orig_exe;
#endif

	// Update-mode is running?
	if (QApplication::arguments().contains("--update-mode")) {
		this->tmp_dir = this->orig_dir;
		this->tmp_datadir = this->tmp_dir + "/update-data";
		QFile fl_o(this->tmp_dir + "/.basepath");
		fl_o.open(QIODevice::ReadOnly);
		this->orig_dir = fl_o.readAll();
	}
}

bool u_update::copy_to_tmp() {
	// Copy our data files to TMP folder
	this->scan_dir(this->orig_dir_in);

	this->tmp_dir = QDir::tempPath() + "/upload-client-update-" + QString::number(qrand());
#ifdef Q_OS_MAC
	this->tmp_dir += ".app";
#endif
	QDir tmp(this->tmp_dir);
	if (!tmp.mkpath(this->tmp_dir))
		return false;

	qDebug() << "TMP: " << this->tmp_dir;

	this->tmp_datadir = this->tmp_dir + "/update-data";
	if (!tmp.mkpath(this->tmp_datadir))
		return false;

	// Okay, now copy our stuff...
	for (int x = 0; x < this->orig_files.count(); x++) {
		QString file_path = this->tmp_dir + this->orig_files.at(x);
		qDebug() << file_path;
		QFileInfo fin(file_path);
		tmp.mkpath(fin.absoluteDir().path());
		if (!QFile::copy(this->orig_dir + this->orig_files.at(x), file_path))
			return false;
	}

	// Save system data
	QFile dt_path(this->tmp_dir + "/.basepath");
	if (!dt_path.open(QIODevice::WriteOnly))
		return false;
	dt_path.write(this->orig_dir.toStdString().c_str());
	dt_path.close();

	return true;
}

void u_update::run_from_tmp() {
	//
	qDebug() << "Running: " << this->tmp_dir + "/" + this->orig_exe;
	// Okay, now we run...
	QProcess *upd_proc = new QProcess();
	QStringList args;
	args << "--update-mode";
	upd_proc->startDetached(this->tmp_dir + "/" + this->orig_exe, args, this->tmp_dir);
	core->exit();
}

void u_update::check_updates() {
	this->state = CheckUpdates;
	this->ui->show();
	emit this->status_changed();

	this->scan_dir(this->orig_dir_in);
	QStringList files_md5;
	for (int x = 0; x < this->orig_files.count(); x++) {
		// qDebug() << this->orig_files.at(x);
		QFile fin(this->orig_dir + "/" + this->orig_files.at(x));
		if (!fin.open(QIODevice::ReadOnly)) {
			continue;
		}
		QString file_md5 = QCryptographicHash::hash(fin.readAll(), QCryptographicHash::Md5).toHex();
		// qDebug() << this->orig_files.at(x) << file_md5;
		file_md5 = QCryptographicHash::hash(QString(this->orig_files.at(x) + file_md5).toStdString().c_str(), QCryptographicHash::Md5).toHex();
		files_md5 << file_md5;
		qDebug() << this->orig_files.at(x) << file_md5;
	}

	u_api *api = new u_api(this);
	api->std_request();
	api->set_action("client-update");

	api->post_data = "flist=" + files_md5.join("|");

	if (!api->do_action()) {
		QMessageBox::warning(this->ui, tr("Update error!"), tr("Error during updating - please, try again later"));
		return;
	}

	// Okay, we got The list!
	QDomElement upd_el = api->ans_dom.documentElement().childNodes().at(0).toElement();

	QString html_desc = "";

	QDomElement v_d = upd_el.firstChildElement("info");
	for (int x = 0; x < v_d.childNodes().count(); x++) {
		QDomNode v_dd = v_d.childNodes().at(x);
		html_desc += "<h3><span style='color:gray;'>" + QDateTime::fromTime_t(v_dd.attributes().namedItem("tms_publish").nodeValue().toInt()).toString("dd MMM yyyy") + " - </span>" + v_dd.attributes().namedItem("version").nodeValue() + "</h3>";
		html_desc += "<p>" + v_dd.childNodes().at(0).nodeValue() + "</p>";
	}

	this->ui->ui->txtDetails->setHtml(html_desc);

	QDomElement v_fl = upd_el.firstChildElement("files");
	for (int x = 0; x < v_fl.childNodes().count(); x++) {
		QDomNode v_dd = v_fl.childNodes().at(x);
		_upd_file *fl = new _upd_file;
		fl->state = _upd_file::Wait;
		fl->dsize = 0;
		fl->size = v_dd.attributes().namedItem("size").nodeValue().toInt();
		this->size_total += fl->size;
		fl->name = v_dd.attributes().namedItem("name").nodeValue();
		fl->url = QUrl(v_dd.attributes().namedItem("url").nodeValue());

		this->d_files.append(fl);
	}

	this->state = ReadyStart;
	emit this->status_changed();
}

_upd_file *u_update::get_d_status(_upd_file::_state st) {
	for (int x = 0; x < this->d_files.count(); x++) {
		if (this->d_files.at(x)->state == st)
			return this->d_files.at(x);
	}
	return NULL;
}

void u_update::scan_dir(QString fname) {
	QFileInfo finf(this->orig_dir + fname);
	if (finf.isDir()) {
		// It is a dir...
		QDir dr(this->orig_dir + fname);
		QStringList dr_data = dr.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
		if (fname != "/")
			fname += "/";
		for (int x = 0; x < dr_data.count(); x++) {
			this->scan_dir(fname + dr_data.at(x));
		}
	} else {
		// File?
		this->orig_files << fname;
	}
}

void u_update::remove_dir(QString fname) {
	QFileInfo finf(fname);
	if (finf.isDir()) {
		// It is a dir...
		QDir dr(fname);
		QStringList dr_data = dr.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
		for (int x = 0; x < dr_data.count(); x++) {
			if (dr_data.at(x) == "." || dr_data.at(x) == "..")
				continue;
			u_update::remove_dir(fname + "/" + dr_data.at(x));
		}
		dr.rmpath(fname);
		// QMessageBox::information(0,"","RemoveDir: " + fname);
	} else {
		// File?
		QFile::remove(fname);
		// QMessageBox::information(0,"","RemoveFile: " + fname);
	}
}

void u_update::start_update() {
	this->state = Downloading;
	emit this->status_changed();

	// Start 1-st file
	this->_down_done(NULL);
}

void u_update::cancel() {
	int res = QMessageBox::question(this->ui, tr("Are you sure?"), tr("Are you sure waht you want to stop update process?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::No)
		return;

	if (this->state == ReadyStart || this->state == CheckUpdates) {
		this->run_from_orig();
		core->exit();
		return;
	}
}

bool u_update::copy_dir(QString from, QString to) {
	QFileInfo infin(from);
	if (infin.isDir()) {
		// This is a DIR - scan contents
		QDir().mkpath(to);
		QDir dr(from);
		QStringList dr_data = dr.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
		for (int x = 0; x < dr_data.count(); x++) {
			if (!this->copy_dir(from + "/" + dr_data.at(x), to + "/" + dr_data.at(x)))
				return false;
		}
	} else {
		// This is a file - just copy to the new location
		// QMessageBox::information(0,"","Copy: " + from + " - " + to);
		QFile::remove(to);
		if (!QFile::copy(from, to))
			return false;

#ifdef Q_OS_LINUX
		chmod(to.toStdString().c_str(), 0777);
#endif
#ifdef Q_OS_MAC
		chmod(to.toStdString().c_str(), 0777);
#endif
	}
	return true;
}

void u_update::_down_progress(qint64 down, qint64 total) {
	this->size_downloaded = 0;
	_upd_file *cr = this->get_d_status(_upd_file::Download);
	cr->size = total;
	cr->dsize = down;

	for (int x = 0; x < this->d_files.count(); x++) {
		if (this->d_files.at(x)->state == _upd_file::Download || this->d_files.at(x)->state == _upd_file::Downloaded)
			this->size_downloaded += this->d_files.at(x)->dsize;
	}

	int pers = ((double)this->size_downloaded / (double)this->size_total) * (double)100;
	emit this->progress_chagned(pers);
}
void u_update::_down_done(QNetworkReply *rep) {
	if (rep) {
		// Stop last
		_upd_file *last = this->get_d_status(_upd_file::Download);
		// Save file..
		if (last) {
			// ...
			last->state = _upd_file::Downloaded;
			qDebug() << "Saving: " << last->name << " to: " << this->tmp_datadir + last->name;
			QFileInfo fn(this->tmp_datadir + last->name);
			QDir().mkpath(fn.dir().absolutePath());
			QFile fl_o(this->tmp_datadir + last->name);
			if (!fl_o.open(QIODevice::WriteOnly)) {
				QMessageBox::warning(0, tr("File save error!"), tr("Enable save file to TMP directory: '%1'!").arg(this->tmp_datadir + last->name));
				this->run_from_orig();
				return;
			}
			fl_o.write(rep->readAll());
			fl_o.close();
		}
	}
	// Start next
	_upd_file *next = this->get_d_status(_upd_file::Wait);
	if (!next) {
		// All done!
		qDebug() << "All done!";

		this->state = CopyToMain;
		emit this->status_changed();

		this->copy_to_main();

		return;
	}

	next->state = _upd_file::Download;

	QNetworkRequest req;
	req.setUrl(next->url);
	QNetworkReply *new_rep = this->mng->get(req);
	connect(new_rep, SIGNAL(downloadProgress(qint64, qint64)), SLOT(_down_progress(qint64, qint64)));
	// qDebug() << "Started: " << next->url;
	// QMessageBox::information(0,next->url.toString(),"");
}

void u_update::copy_to_main() {
	// Copy data dir to dist dir...
	if (!this->copy_dir(this->tmp_datadir, this->orig_dir)) {
		QMessageBox::warning(this->ui, tr("Copy file error"), tr("Enable to copy new file(s) to '%1'. Check permissions and try again.").arg(this->orig_dir));
	}

	this->run_from_orig();
}

void u_update::run_from_orig() {
	// Start updated program!
	// QMessageBox::information(0,"","Run: " + this->orig_dir + "/" + this->orig_exe);
	QProcess proc;
	QStringList arg;
	arg << "--clean" << this->tmp_dir;
	proc.startDetached(this->orig_dir + "/" + this->orig_exe, arg, this->orig_dir);
	core->exit();
}
