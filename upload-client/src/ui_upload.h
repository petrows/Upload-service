#ifndef UI_UPLOAD_H
#define UI_UPLOAD_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QTreeView>
#include <math.h>

#include "global.h"

#include "u_core.h"
#include "u_upload.h"
#include "ui_wdg_flist.h"

namespace Ui {
	class ui_upload;
}

class ui_upload : public QDialog
{
	Q_OBJECT

public:
	explicit ui_upload(QWidget *parent, u_upload * upl);
	~ui_upload();

	ui_wdg_flist * f_list;
	u_upload  * upl;

public slots:
	void reload ();
	void btnStateSave(bool is_work = false);
	void btnStateDelete(bool is_work = false);

private slots:
	void on_btnSave_clicked();

	void on_btnDelete_clicked();

	void on_btnCancel_clicked();

private:
	Ui::ui_upload *ui;
};

#endif // UI_UPLOAD_H
