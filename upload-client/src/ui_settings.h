#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QDialog>
#include "global.h"

#include "u_core.h"

namespace Ui {
    class ui_settings;
}

class ui_settings : public QDialog
{
    Q_OBJECT

public:
    explicit ui_settings(QWidget *parent = 0);
    ~ui_settings();
	
	QList< QPair<QString,QString> > langs;


private slots:
	void on_btnCheck_clicked();
	void on_btnOk_clicked();
	void on_btnCancel_clicked();

private:
    Ui::ui_settings *ui;
};

#endif // UI_SETTINGS_H


