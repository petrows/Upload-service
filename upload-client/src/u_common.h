#ifndef U_COMMON_H
#define U_COMMON_H

#include "global.h"

#define USE_ZIP

#ifdef USE_ZIP

#include "quazip.h"
#include "quazipfile.h"
#include "quazipfileinfo.h"
#include "quazipnewinfo.h"

class zip_pack : public QObject {
	Q_OBJECT

public:
	explicit zip_pack(QObject *parent = 0);
	~zip_pack();

	bool unlink_on_exit;

	QString zip_out;
	QStringList zip_files_ok;
	QList<QPair<QString, QString> > files_in;
	bool pack_files(QStringList files);

	qint64 zip_size();
	int files_total();
	int files_done();

	QString last_error;

private:
	void sc_files(QString root, QString fname);
	QuaZip *zp;
	int _fc_done;
	int _fc_total;
signals:
	void error(QString);
	void file_added(QString, QString);
	void file_started(QString, QString);
	void file_progress(qint64 done, qint64 total);
	void started();
	void finished();
};

#endif // USE_ZIP

quint32 perms_hex2oct(quint32 phex);

#endif // U_COMMON_H
