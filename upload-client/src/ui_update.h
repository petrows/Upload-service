#ifndef UI_UPDATE_H
#define UI_UPDATE_H

#include <QDialog>
#include "global.h"

namespace Ui {
    class ui_update;
}

class ui_update : public QDialog
{
    Q_OBJECT
public:
    explicit ui_update(QWidget *parent = 0);
    ~ui_update();

	u_update * upd;

	void init ();
	void closeEvent(QCloseEvent *);

    Ui::ui_update *ui;

public slots:
	void reload_ui ();
};

#endif // UI_UPDATE_H
