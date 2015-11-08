#include "ui_askwindow.h"
#include "ui_ui_askwindow.h"

ui_askwindow::ui_askwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ui_askwindow)
{
    ui->setupUi(this);
}

ui_askwindow::~ui_askwindow()
{
    delete ui;
}

int ui_askwindow::exec()
{
	QDialog::exec();

	return 55;
}
