#ifndef U_CORE_H
#define U_CORE_H

#include <QSystemTrayIcon>
#include <QNetworkProxy>

#include "global.h"

#include "md5.h"

#include "u_upload.h"
#include "u_api.h"

#include "ui_init.h"
#include "ui_main.h"
#include "ui_settings.h"
#include "ui_upload.h"

class u_core_sleep: public QThread
{
public:
	static void msleep(int ms);
};

class u_core : public QObject
{
	Q_OBJECT
public:
	explicit u_core(QObject *parent = 0);
	~u_core();

	ui_main * _ui_main;
	ui_init * _ui_init;

	QSettings cfg;
	QList<u_upload*> uploads;

	QList< QPair<int,QString> > ttls;
	int ttl_default;

	QString os;
	QString version_s;
	int     version_i[3];
	QString build_tms;

	QString sid;
	QString lk;
	int     uid;
	QString login;
	QString passw;
	QString name;

	int     uploads_seed;

	bool    upd_has;
	QString upd_v;

	int     opt_upd_ask_period;
	int     opt_upd_ask_last;

	bool    opt_proxy_enable;
	QString opt_proxy_type;
	QString opt_proxy_host;
	int     opt_proxy_port;

	char    opt_zip_files;
	QString tmp_folder;

	QSystemTrayIcon * tray;
	QAction         * tract_show;
	QAction         * tract_new_upload;
	QAction         * tract_exit;

	bool       last_complete_was;
	u_upload * last_complete;

	void run ();
	void reload_config ();
	void start_new_sid ();

	bool sid_ready ();
	
	bool has_uploading();

	// Common functions
	static QString format_size (qint64 sz);
	static QString str_md5(QString in);

signals:
	void global_state_changed();
public slots:
	void exit();
	void reload_ui();
	void start_update ();
	void toggle_main_wnd();
	void tray_activate(QSystemTrayIcon::ActivationReason res);
	void tray_msg_click();
	void start_new_upload (QStringList in = QStringList());
	void qsa_message(QString msg);

	void tmsg_copy_link();
	void tmsg_complete(u_upload * upl);

	void open_link(QString url);

private:
	QStringList _scan_upl_folders(QString fname);
};

#endif // U_CORE_H
