#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QMainWindow>
#include "global.h"

#include "u_core.h"
#include "ui_wdg_ulist.h"

namespace Ui {
class ui_main;
}

class ui_main : public QMainWindow
{
	Q_OBJECT

public:
	explicit ui_main(QWidget *parent = 0);
	~ui_main();

	ui_wdg_ulist * ulist;

	void closeEvent(QCloseEvent *);
	void dragEnterEvent(QDragEnterEvent *);
	void dropEvent(QDropEvent *);

public slots:
	void on_actionHide_triggered();
	void on_actionExit_triggered();
	void on_actionNew_upload_triggered();
	void on_actionSettings_triggered();
	void upd();
private slots:
	void on_btnNewUpload_clicked();

	void on_actionAbout_program_triggered();

	void on_actionHome_page_triggered();

	void on_actionAbout_Qt_triggered();

private:
	Ui::ui_main *ui;
};

#endif // UI_MAIN_H

