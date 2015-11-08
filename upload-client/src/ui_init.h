#ifndef UI_INIT_H
#define UI_INIT_H

#include <QDialog>
#include "global.h"

#include "u_core.h"

namespace Ui {
    class ui_init;
}

class ui_init : public QDialog
{
    Q_OBJECT

public:
    explicit ui_init(QWidget *parent = 0);
    ~ui_init();

	void closeEvent(QCloseEvent *);

private slots:
	void on_btnCancel_clicked();

private:
    Ui::ui_init *ui;
};

#endif // UI_INIT_H
