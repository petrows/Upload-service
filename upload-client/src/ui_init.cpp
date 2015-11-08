#include "ui_init.h"
#include "ui_ui_init.h"

ui_init::ui_init(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ui_init)
{
    ui->setupUi(this);
}

ui_init::~ui_init()
{
    delete ui;
}

void ui_init::closeEvent(QCloseEvent * ev)
{
	// Fuck off
	QDialog::closeEvent(ev);
}

void ui_init::on_btnCancel_clicked()
{
	core->exit();
}
