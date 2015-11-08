#include "ui_about.h"
#include "ui_ui_about.h"

#include "u_core.h"

ui_about::ui_about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ui_about)
{
    ui->setupUi(this);

	connect(ui->lblOwner,SIGNAL(linkActivated(QString)),core,SLOT(open_link(QString)));
	connect(ui->lblIconPacks,SIGNAL(linkActivated(QString)),core,SLOT(open_link(QString)));

	ui->lblBuildDate->setText(core->build_tms);
	ui->lblVersion->setText(core->version_s);
}

ui_about::~ui_about()
{
    delete ui;
}

void ui_about::on_btnClose_clicked()
{
	this->close();
}
