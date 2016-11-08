#ifndef U_UPLOAD_H
#define U_UPLOAD_H

#include "global.h"

#include "ui_upload.h"
#include "u_api.h"

class u_upload;
class u_upload_file;

class u_upload_file : public QObject
{
	Q_OBJECT
public:
	explicit u_upload_file(QObject *parent = 0);

	QMutex mtx_info;

	enum FileState {
		Idle      = 1,
		Uploading = 2,
		Uploaded  = 3,
		Error     = 4
	} state;

	u_upload * parent;

	QFile   file_h;
	QNetworkAccessManager mng;
	QNetworkReply * rep;

	QDateTime upload_starts;

	QString file_dh;
	QString file_name;
	int     file_n;
	qint64  file_size;
	qint64  file_size_uploaded;
	QString file_local;

	QProgressBar * progr_flist;

	QString last_error;

	bool start_upload(QString path);
	float file_progress();

	QString file_link();


signals:
	void progress (qint64 done, qint64 total);
	void status_changed ();
	void state_changed (u_upload_file::FileState state);
public slots:
	void flist_progr_del();
	void copy_file_link();
private slots:
	void _progress (qint64 done, qint64 total);
	void _req_done ();
};

class u_upload : public QObject
{
	Q_OBJECT
public:
	explicit u_upload(QObject *parent = 0);
	~u_upload();

	QMutex mtx_info;

	enum UploadState {
		Idle      = 1,
		Uploading = 2,
		Uploaded  = 3,
		Error     = 4
	} state;

	ui_upload * form;

	bool remove_after_upload;

	QString title;
	QString last_error;

	quint64 size_upoaded;
	quint64 size_total;

	QDateTime tm_created;
	QDateTime tm_delete;
	QDateTime tm_last;

	int       id;
	int       up_id;
	int       ttl;
	bool      prolong;
	QString   sid;

	QString   code;
	QString   ph;

	QProgressBar * progr_ulist;

	QNetworkAccessManager mng;
	u_api     *api;

	QList<u_upload_file*> files;

	float total_progress();
	int files_count();
	int files_uploading_count();
	int avg_speed ();
	void recount();

	void add_file_itm(u_upload_file * fl);

	void update_state();

	bool has_files_ok();
	bool has_files_error();
	bool has_files_uploading();
	bool has_files_status(u_upload_file::FileState state);

	bool deleteMe(bool force = false);
	bool setInfo(QString comment,int ttl,bool prolong);

	QString ttl_color();
	QString ttl_date();
	QString ttl_period();

	QString get_title ();

	bool start_file (QString path);

	QString public_link();

signals:
	void upload_progress (qint64 done, qint64 total);
	void update_info ();

public slots:
	void file_upload_progress (qint64 done, qint64 total);
	void file_upload_status (u_upload_file::FileState state);
	void status_recheck ();
	void ulist_progr_del();
	void copy_upload_link();
	void show_form ();
	void update_form ();
};

#endif // U_UPLOAD_H
