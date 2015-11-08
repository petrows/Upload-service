#ifndef U_UPDATE_H
#define U_UPDATE_H

#include <QObject>
#include "global.h"

struct _upd_file
{
	QString name;
	int     size;
	int     dsize;
	QUrl    url;
	enum _state{Wait,Download,Downloaded} state;
};

class u_update : public QObject
{
	Q_OBJECT
public:
	explicit u_update(QObject *parent = 0);
	
	u_api * api;
	
	QString        orig_dir;
	QString        orig_dir_in;
	QStringList    orig_files;
	QString        orig_exe;

	QString        tmp_dir;
	QString        tmp_datadir;

	int  size_total;
	int  size_downloaded;

	QList<_upd_file*> d_files;

	QString v_desc;
	
	enum {CheckUpdates,ReadyStart,Downloading,CopyToMain} state;

	ui_update * ui;
	QNetworkAccessManager * mng;
	
	void check_updates ();
	bool copy_to_tmp ();
	void copy_to_main ();
	void run_from_tmp ();
	void run_from_orig ();

	static void remove_dir (QString dir);

private:
	void scan_self ();
	void scan_dir (QString dir);
	bool copy_dir (QString from, QString to);

	_upd_file* get_d_status(_upd_file::_state);

signals:
	void status_changed();
	void progress_chagned(int);
public slots:
	void cancel();
	void start_update();
private slots:
	void _down_progress(qint64 down, qint64 total);
	void _down_done(QNetworkReply*);
};

#endif // U_UPDATE_H
