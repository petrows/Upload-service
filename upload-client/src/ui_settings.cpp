#include "ui_settings.h"
#include "ui_ui_settings.h"

ui_settings::ui_settings(QWidget *parent) : QDialog(parent), ui(new Ui::ui_settings) {
	this->langs.append(qMakePair(QString("ru_ru"), QString("Russian (Русский)")));
	this->langs.append(qMakePair(QString("en_US"), QString("English")));

	ui->setupUi(this);

	ui->edtLogin->setText(core->cfg.value("login").toString());
	ui->edtPassword->setText(core->cfg.value("passw").toString());

	QList<QPair<QString, int> > updt_list;
	updt_list.append(qMakePair(tr("Once a day"), 86400));
	updt_list.append(qMakePair(tr("Once a week"), 7 * 86400));
	updt_list.append(qMakePair(tr("Once a month"), 30 * 86400));
	updt_list.append(qMakePair(tr("Never"), -1));
	int updt_sel_index = 0;
	for (int x = 0; x < updt_list.count(); x++) {
		this->ui->boxUpdPeriod->addItem(updt_list.at(x).first, updt_list.at(x).second);
		if (updt_list.at(x).second == core->opt_upd_ask_period)
			updt_sel_index = x;
	}
	this->ui->boxUpdPeriod->setCurrentIndex(updt_sel_index);

	this->ui->rbtZipAsk->setChecked('S' == core->opt_zip_files);
	this->ui->rbtZipAlways->setChecked('A' == core->opt_zip_files);
	this->ui->rbtZipNever->setChecked('N' == core->opt_zip_files);

	this->ui->boxProxyType->addItem("HTTP", "HTTP");
	this->ui->boxProxyType->addItem("SOCKS 5", "SOCKS5");
	for (int x = 0; x < ui->boxProxyType->count(); x++) {
		if (ui->boxProxyType->itemData(x).toString() == core->opt_proxy_type) {
			this->ui->boxProxyType->setCurrentIndex(x);
			break;
		}
	}
}

ui_settings::~ui_settings() { delete ui; }

void ui_settings::on_btnCheck_clicked() {
	this->ui->btnCheck->setDisabled(true);
	this->ui->edtLogin->setDisabled(true);
	this->ui->edtPassword->setDisabled(true);

	// Start check...
	u_api api;
	api.sid = "";
	api.login = this->ui->edtLogin->text();
	api.passw = this->ui->edtPassword->text();
	api.std_request();
	api.set_action("check");

	bool res = api.do_action();
	QMessageBox msg;
	msg.setStandardButtons(QMessageBox::Ok);
	msg.setWindowTitle(tr("Login check results"));
	if (res) {
		msg.setIcon(QMessageBox::Information);
		msg.setText(tr("Login is OK!"));
	} else {
		msg.setIcon(QMessageBox::Warning);
		msg.setText(tr("Invalid login!"));
	}
	msg.exec();
	this->ui->btnCheck->setDisabled(false);
	this->ui->edtLogin->setDisabled(false);
	this->ui->edtPassword->setDisabled(false);
}

void ui_settings::on_btnOk_clicked() {
	core->cfg.setValue("saved", true);
	core->cfg.setValue("login", this->ui->edtLogin->text());
	core->cfg.setValue("passw", this->ui->edtPassword->text());
	core->cfg.setValue("update/ask_period", this->ui->boxUpdPeriod->itemData(this->ui->boxUpdPeriod->currentIndex()).toInt());

	char z_mode = 'S';
	if (this->ui->rbtZipAsk->isChecked())
		z_mode = 'S';
	if (this->ui->rbtZipAlways->isChecked())
		z_mode = 'A';
	if (this->ui->rbtZipNever->isChecked())
		z_mode = 'N';
	core->cfg.setValue("zip_files_mode", QChar(z_mode));

	core->cfg.setValue("proxy/enable", this->ui->grpProxy->isChecked());
	core->cfg.setValue("proxy/type", ui->boxProxyType->itemData(ui->boxProxyType->currentIndex()).toString());
	core->cfg.setValue("proxy/host", this->ui->edtProxyIp->text());
	core->cfg.setValue("proxy/port", this->ui->edtProxyPort->text().toInt());

	core->cfg.sync();
	core->reload_config();
	this->close();
}
void ui_settings::on_btnCancel_clicked() { this->close(); }
