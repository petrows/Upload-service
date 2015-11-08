#include "u_upload.h"

#include <QFileInfo>
#include <QClipboard>

#include "u_api.h"

// ======================================================================

u_upload_file::u_upload_file(QObject *parent) :
	QObject(parent)
{
	this->upload_starts = QDateTime::currentDateTime();
	this->file_size          = 0;
	this->file_size_uploaded = 0;
	this->progr_flist   = NULL;
	connect(this,SIGNAL(status_changed()),core,SLOT(reload_ui()));
}

bool u_upload_file::start_upload(QString path)
{
	this->state = u_upload_file::Uploading;

	this->file_h.setFileName(path);
	if (!this->file_h.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QFileInfo file_inf(path);

	if (!file_inf.isFile())
		return false;

	this->file_local = path;

	u_api api;

	QNetworkRequest req = api.std_request();
	QUrl            req_url("http://"UPLOAD_DOMAIN"/upload.cgi?api=1&s="+core->sid);
	req_url.addQueryItem("upid",QString::number(this->parent->up_id));
	req_url.addQueryItem("id",QString::number(this->parent->files.count()));
	req_url.addQueryItem("qqfile",file_inf.fileName());

	this->file_size = file_inf.size();
	this->file_name = file_inf.fileName();

	req.setUrl(req_url);

	QString ss_cookie = api.std_cookies();
	ss_cookie += "; auth="+(core->lk);
	req.setRawHeader("Cookie", ss_cookie.toStdString().c_str());

	this->rep = this->mng.post(req, &this->file_h);
	connect(this->rep,SIGNAL(uploadProgress(qint64,qint64)),SLOT(_progress(qint64,qint64)));
	connect(this->rep,SIGNAL(finished()),SLOT(_req_done()));

	this->upload_starts = QDateTime::currentDateTime();

	this->state = Uploading;

	this->parent->update_form();
	emit this->status_changed();
	return true;
}

float u_upload_file::file_progress()
{
	if (this->state != Uploading)
		return 100.0f;
	if (!this->file_size_uploaded || !this->file_size)
		return 0.0f;

	return ((long double)this->file_size_uploaded/(long double)this->file_size)*100.0f;
}

void u_upload_file::_progress(qint64 done, qint64 total)
{
	// Code to prevent send signals too fast...
	static time_t fz_tm = 0;
	if (fz_tm == time(NULL))
		return;
	fz_tm = time(NULL);

	this->mtx_info.lock();
	this->file_size          = total;
	this->file_size_uploaded = done;
	this->mtx_info.unlock();
	emit this->progress(done, total);
}
void u_upload_file::_req_done()
{
	if (this->parent->remove_after_upload)
	{
		qDebug() << "Removing file: " << this->file_local;
		QFile::remove(this->file_local);
	}

	// Read ans
	u_api api;
	if (!api.parse_answer(rep->readAll()) || api.ans_dom.documentElement().firstChildElement("upload").attributes().namedItem("status").nodeValue()!="ok")
	{
		// Error!
		this->state      = Error;
		this->last_error = api.last_error;
		emit this->status_changed();
		return;
	}


	// Okay check ans...
	QDomElement api_ans = api.ans_dom.documentElement().firstChildElement("upload");
	this->parent->id    = api_ans.attributes().namedItem("upload_id").nodeValue().toInt();
	this->parent->code  = api_ans.attributes().namedItem("upload_code").nodeValue();
	this->parent->ph    = api_ans.attributes().namedItem("upload_ph").nodeValue();
	this->parent->ttl   = api_ans.attributes().namedItem("ttl").nodeValue().toInt();
	this->parent->tm_last    = QDateTime::fromTime_t(api_ans.attributes().namedItem("tms_last").nodeValue().toInt());
	this->parent->tm_delete  = QDateTime::fromTime_t(api_ans.attributes().namedItem("tms_delete").nodeValue().toInt());
	this->parent->prolong    = api_ans.attributes().namedItem("prolong").nodeValue() == "Y";
	this->file_n        = api_ans.attributes().namedItem("file_n").nodeValue().toInt();
	this->file_dh       = api_ans.attributes().namedItem("file_dh").nodeValue();

	this->state = Uploaded;
	emit this->status_changed();
	this->parent->recount();
	core->reload_ui();
}

void u_upload_file::flist_progr_del()
{
	this->progr_flist = NULL;
}

QString u_upload_file::file_link()
{
	return "http://"UPLOAD_DOMAIN"/download/"+this->parent->code+"/"+QString::number(this->file_n)+"/"+this->file_dh+"/"+QUrl::toPercentEncoding(this->file_name);
}

void u_upload_file::copy_file_link()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(this->file_link());
	core->tmsg_copy_link();
}

// ======================================================================
// ======================================================================

u_upload::u_upload(QObject *parent) :
    QObject(parent)
{
	this->state        = Uploaded;
	this->id           = 0;
	this->size_total   = 0;
	this->size_upoaded = 0;
	this->form         = NULL;
	this->api          = NULL;
	this->progr_ulist  = NULL;
	this->up_id        = core->uploads_seed++;
	this->tm_created   = QDateTime::currentDateTime();
	this->tm_last      = QDateTime::currentDateTime();
	this->tm_delete    = QDateTime::currentDateTime();
	this->remove_after_upload = false;
}

u_upload::~u_upload()
{
	if (this->form)
		delete this->form;
	if (this->api)
		delete this->api;
}

void u_upload::ulist_progr_del()
{
	this->progr_ulist = NULL;
}

QString u_upload::public_link()
{
	return "http://"UPLOAD_DOMAIN"/f/"+this->code+"/"+this->ph+"/";
}

void u_upload::copy_upload_link()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(this->public_link());
	core->tmsg_copy_link();
}

bool u_upload::deleteMe(bool force)
{
	if (this->api)
		delete this->api;

	this->api = new u_api(this);

	this->api->std_request();

	this->api->set_action("delete");
	this->api->req_url.addQueryItem("id",QString::number(this->id));
	bool res = this->api->do_action();

	if (!res && !force)
		return false;

	// qDebug() << core->uploads.count();
	core->uploads.removeAt(core->uploads.indexOf(this));
	// qDebug() << core->uploads.count();
	// delete this;
	this->deleteLater();
	return true;
}
bool u_upload::setInfo(QString comment, int ttl, bool prolong)
{
	if (this->api)
		delete this->api;

	this->api = new u_api(this);

	this->api->std_request();

	this->api->set_action("update");
	this->api->req_url.addQueryItem("id",QString::number(this->id));
	this->api->req_url.addQueryItem("comment",comment);
	this->api->req_url.addQueryItem("ttl",QString::number(ttl));
	this->api->req_url.addQueryItem("prol",prolong?"Y":"N");
	bool res = this->api->do_action();
	if (res)
	{
		QDomNode ans = this->api->ans_dom.documentElement().elementsByTagName("update").at(0);
		if (ans.attributes().namedItem("status").nodeValue() != "ok")
			return false;
		this->ttl       = ans.attributes().namedItem("ttl").nodeValue().toInt();
		this->tm_delete = QDateTime::fromTime_t(ans.attributes().namedItem("tms_delete").nodeValue().toInt());
		this->tm_last   = QDateTime::fromTime_t(ans.attributes().namedItem("tms_last").nodeValue().toInt());
		this->prolong   = ans.attributes().namedItem("prolong").nodeValue()=="Y";
		this->title     = comment;
	}
	return res;
}

QString u_upload::ttl_date()
{
	if (QDateTime::currentDateTime().secsTo(this->tm_delete) < 24*3600)
	{
		// Less a day!
		return this->tm_delete.toString("hh:mm");
	}
	return this->tm_delete.toString("d.MM.yyyy");
}
QString u_upload::ttl_color()
{
	int tm_now = QDateTime::currentDateTime().toTime_t();
	int tm_del = this->tm_delete.toTime_t();
	int tm_str = 0;
	if (this->prolong)
		tm_str = this->tm_last.toTime_t();
	else
		tm_str = this->tm_created.toTime_t();

	int t  = tm_del - tm_str;
	int tn = tm_del - tm_now;

	float pers = (double)tn/(double)t;

	if (pers < 0.3)
		return "red";
	if (pers < 0.6)
		return "#FF8000";

	return "green";
}

QString u_upload::ttl_period()
{
	time_t sec2del = QDateTime::currentDateTime().secsTo(this->tm_delete);

	if (sec2del <= 3600)
		return QString().sprintf("%.0f ",round((double)sec2del/(double)(60))) + tr("min(s)");
	if (sec2del <= 24*3600)
		return QString().sprintf("%.0f ",round((double)sec2del/(double)(3600))) + tr("hour(s)");

	return QString().sprintf("%.0f ",round((double)sec2del/(double)(24*3600))) + tr("day(s)");
}

void u_upload::show_form()
{
	this->update_state();
	if (!this->form)
	{
		this->form      = new ui_upload(0, this);
		this->form->upl = this;
	}
	this->form->reload();
	this->form->show();
	this->form->activateWindow();
}

void u_upload::update_form()
{
	if (this->form)
	{
		this->form->reload();
	}
	if (this->progr_ulist)
		this->progr_ulist->setValue(this->total_progress());
}

void u_upload::update_state()
{
	if (this->has_files_uploading())
	{
		this->state = Uploading;
		return;
	}
	if (this->has_files_error() && !this->has_files_ok() && !this->has_files_uploading())
	{
		this->state = Error;
		return;
	}
	if (this->has_files_ok())
	{
		if (this->state != Uploaded)
		{
			// Status changed...
			core->tmsg_complete(this);
		}
		this->state = Uploaded;
		return;
	}
	this->state = Idle;
	this->recount();
	core->reload_ui();
}

void u_upload::recount()
{
	this->mtx_info.lock();
	this->size_total = 0;
	this->size_upoaded = 0;

	for (int x=0; x<this->files.count(); x++)
	{
		// Get file info
		this->files.at(x)->mtx_info.lock();
		this->size_total += this->files.at(x)->file_size;
		this->size_upoaded += this->files.at(x)->file_size_uploaded;
		this->files.at(x)->mtx_info.unlock();
	}
	this->mtx_info.unlock();
}

void u_upload::add_file_itm(u_upload_file *fl)
{
	fl->parent = this;
	connect(fl,SIGNAL(status_changed()),this,SLOT(status_recheck()));
	this->files.append(fl);
}

bool u_upload::has_files_ok()
{
	return this->has_files_status(u_upload_file::Uploaded);
}
bool u_upload::has_files_error()
{
	return this->has_files_status(u_upload_file::Error);
}
bool u_upload::has_files_uploading()
{
	return this->has_files_status(u_upload_file::Uploading);
}

bool u_upload::has_files_status(u_upload_file::FileState state)
{
	this->mtx_info.lock();
	bool res = false;
	for (int x=0; x<this->files.count(); x++)
	{
		// Get file info
		this->files.at(x)->mtx_info.lock();
		res = this->files.at(x)->state == state;
		this->files.at(x)->mtx_info.unlock();
		if (res)
			break;
	}
	this->mtx_info.unlock();
	return res;
}

float u_upload::total_progress()
{
	if (this->state != Uploading)
		return 100.0f;
	if (!this->size_upoaded || !this->size_total)
		return 0.0f;

	return ((long double)this->size_upoaded/(long double)this->size_total)*100.0f;
}

int u_upload::files_count()
{
	return this->files.size();
}

int u_upload::files_uploading_count()
{
	this->mtx_info.lock();
	int res = 0;
	for (int x=0; x<this->files.count(); x++)
	{
		// Get file info
		this->files.at(x)->mtx_info.lock();
		if (this->files.at(x)->state == u_upload_file::Uploading)
			res++;
		this->files.at(x)->mtx_info.unlock();
	}
	this->mtx_info.unlock();
	return res;
}

int u_upload::avg_speed()
{
	this->mtx_info.lock();
	qint64 total_upl = 0;
	int upl_count = 0;
	QDateTime curr_time = QDateTime::currentDateTime();
	for (int x=0; x<this->files.count(); x++)
	{
		// Get file info
		this->files.at(x)->mtx_info.lock();
		if (this->files.at(x)->state == u_upload_file::Uploading)
		{
			// qDebug() << this->files.at(x)->file_size_uploaded;
			if (this->files.at(x)->file_size_uploaded > 0)
			{
				total_upl += (long double)this->files.at(x)->file_size_uploaded / (long double)(-curr_time.secsTo(this->files.at(x)->upload_starts));
				upl_count++;
			}
		}
		this->files.at(x)->mtx_info.unlock();
	}
	this->mtx_info.unlock();
	if (total_upl < 10)
		return 0;
	return (long double)total_upl/upl_count;
}

bool u_upload::start_file(QString path)
{
	// Starting upload a file!

	u_upload_file * fl = new u_upload_file();
	fl->parent = this;
	if (!fl->start_upload(path))
	{
		delete fl;
		return false; // Error
	}

	// Okay! We are started - connect & add it
	this->add_file_itm(fl);
	connect(fl,SIGNAL(progress(qint64,qint64)),SLOT(file_upload_progress(qint64,qint64)));
	connect(fl,SIGNAL(status_changed()),SLOT(status_recheck()));

	this->status_recheck();

	return true;
}

void u_upload::status_recheck()
{
	this->update_state();
	this->update_form();
}

void u_upload::file_upload_progress(qint64 /*done*/, qint64 /*total*/)
{
	this->mtx_info.lock();

	// Calc total...
	this->size_total   = 0;
	this->size_upoaded = 0;

	for (int x=0; x<this->files.count(); x++)
	{
		// Get file info
		this->files.at(x)->mtx_info.lock();
		this->size_total   += this->files.at(x)->file_size;
		this->size_upoaded += this->files.at(x)->file_size_uploaded;
		this->files.at(x)->mtx_info.unlock();
	}

	this->mtx_info.unlock();
	this->update_form();

	emit this->upload_progress(this->size_upoaded,this->size_total);
}

QString u_upload::get_title()
{
	QMutexLocker lock(&this->mtx_info);

	// Have valid title?
	if (this->title.length())
		return this->title;
	// Have files?
	if (this->files.count() > 0)
	{
		QStringList files_out;
		for (int x=0; x<this->files_count() && x<10; x++)
		{
			files_out.append(this->files.at(x)->file_name);
		}
		return files_out.join(", ");
	}
	return tr("Untitled upload");
}

// ======================================================================
