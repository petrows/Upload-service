#ifndef UI_ZIP_FILES_H
#define UI_ZIP_FILES_H

#include <QDialog>

#include "global.h"
#include "u_common.h"

namespace Ui {
    class ui_zip_files;
}

class ui_zip_files : public QDialog
{
    Q_OBJECT

	zip_pack zip;


public:
    explicit ui_zip_files(QWidget *parent = 0);
    ~ui_zip_files();

	QString zip_out;

	bool start_files (QStringList in);
public slots:
	void pack_started();
	void file_started(QString file, QString name);
	void file_progress(qint64 done, qint64 total);
	void finished();
	void z_error(QString text);

private:
    Ui::ui_zip_files *ui;
};

#endif // UI_ZIP_FILES_H
