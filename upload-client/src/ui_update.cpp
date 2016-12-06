#include "ui_update.h"
#include "ui_ui_update.h"

#include "u_core.h"
#include "u_update.h"

#include <QCloseEvent>

ui_update::ui_update(QWidget *parent) : QDialog(parent), ui(new Ui::ui_update) { ui->setupUi(this); }

ui_update::~ui_update() { delete ui; }

void ui_update::init() {
	connect(this->upd, SIGNAL(progress_chagned(int)), ui->progrMain, SLOT(setValue(int)));
	connect(this->upd, SIGNAL(status_changed()), SLOT(reload_ui()));
	connect(this->ui->btnUpdate, SIGNAL(pressed()), upd, SLOT(start_update()));
	connect(this->ui->btnCancel, SIGNAL(clicked()), upd, SLOT(cancel()));
}

void ui_update::closeEvent(QCloseEvent *e) {
	this->upd->cancel();
	e->ignore();
}

void ui_update::reload_ui() {
	if (upd->state == u_update::CheckUpdates) {
		this->ui->lblStatus->setText(tr("Checking version..."));
		this->ui->btnUpdate->setDisabled(true);
	}
	if (upd->state == u_update::ReadyStart) {
		this->ui->txtDetails->setDisabled(false);
		this->ui->lblStatus->setText(tr("Ready for update! Total size: <b>%1</b>").arg(u_core::format_size(upd->size_total)));
		this->ui->btnUpdate->setDisabled(false);
	}
	if (upd->state == u_update::Downloading) {
		this->ui->lblStatus->setText(tr("Downloading files..."));
		this->ui->btnUpdate->setDisabled(true);
	}
	if (upd->state == u_update::CopyToMain) {
		this->ui->lblStatus->setText(tr("Copying files..."));
		this->ui->btnUpdate->setDisabled(true);
		this->ui->btnCancel->setDisabled(true);
	}
}
