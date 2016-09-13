#include "ui_upload.h"
#include "ui_ui_upload.h"

#include "u_api.h"

#include <QUrlQuery>
#include <math.h>

ui_upload::ui_upload(QWidget *parent, u_upload * upl) :
	QDialog(parent),upl(upl),
	ui(new Ui::ui_upload)
{
	ui->setupUi(this);

	this->setWindowIcon(QIcon(":/icons/upload"));

	this->f_list = new ui_wdg_flist(this,upl);
	this->ui->layoutFiles->addWidget(this->f_list);

	this->ui->btnSave->setIcon(QApplication::style()->standardIcon(QStyle::SP_DriveFDIcon));
	this->ui->btnDelete->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogCancelButton));

	this->btnStateSave(false);
	this->btnStateDelete(false);

	for (int x=0; x<core->ttls.count(); x++)
	{
		this->ui->boxTtl->addItem(core->ttls.at(x).second,x);
	}

	connect(ui->lblPublicLink,SIGNAL(linkActivated(QString)),core,SLOT(open_link(QString)));
}

ui_upload::~ui_upload()
{
	delete ui;
	this->upl->form = NULL; // We are die :(
}

void ui_upload::reload()
{
	// Parts setup
	if (this->upl->state == u_upload::Uploading)
	{
		this->ui->prTotal->setValue(this->upl->total_progress());
		this->setWindowTitle(tr("%1% : Uploading").arg(round(this->upl->total_progress())));
		this->ui->lblUplSize->setText(u_core::format_size(this->upl->size_upoaded));
		this->ui->lblUplSpeed->setText(tr("%1/s").arg(u_core::format_size(this->upl->avg_speed())));
		this->ui->grUploaded->hide();
		this->ui->grUpload->show();
	}
	if (this->upl->state == u_upload::Uploaded)
	{
		this->setWindowTitle(tr("Upload %1 : %2").arg(this->upl->id).arg(this->upl->get_title()));
		this->ui->grUploaded->show();
		this->ui->grUpload->hide();

		this->ui->lblTtl->setText("<span style='color:"+upl->ttl_color()+"'>"+upl->tm_delete.toString("dd MMM yyyy hh:mm")+"</span> - "+upl->ttl_period()+"");
		this->ui->lblPublicLink->setText("<a href='"+upl->public_link()+"'>"+upl->public_link()+"</a>");

		// Search index
		int ttl_index = core->ttl_default;
		for (int x=0; x<core->ttls.count(); x++)
		{
			if (upl->ttl == core->ttls.at(x).first)
			{
				ttl_index = x;
				break;
			}
		}
		this->ui->boxTtl->setCurrentIndex(ttl_index);
		this->ui->edtDescr->setText(upl->title);
		this->ui->chRenew->setChecked(upl->prolong);
	}
	this->f_list->upd();
}

void ui_upload::btnStateSave(bool is_work)
{
	if (is_work)
	{
		this->ui->btnSave->setText(tr("Saving..."));
		this->ui->btnSave->setDisabled(true);
	} else {
		this->ui->btnSave->setText(tr("Save"));
		this->ui->btnSave->setDisabled(false);
	}
}
void ui_upload::btnStateDelete(bool is_work)
{
	if (is_work)
	{
		this->ui->btnDelete->setText(tr("Deleting..."));
		this->ui->btnDelete->setDisabled(true);
	} else {
		this->ui->btnDelete->setText(tr("Delete"));
		this->ui->btnDelete->setDisabled(false);
	}
}

void ui_upload::on_btnSave_clicked()
{
	this->btnStateSave(true);
	this->ui->grUploaded->setDisabled(true);
	u_api api;
	api.set_action("update");
	QUrlQuery urlQuery(api.req_url);
	urlQuery.addQueryItem("id",QString::number(this->upl->id));
	api.req_url.setQuery(urlQuery);

	if (this->upl->setInfo(ui->edtDescr->text(),core->ttls.at(ui->boxTtl->currentIndex()).first,ui->chRenew->checkState()==Qt::Checked))
	{
		this->reload();
		core->reload_ui();

		QMessageBox::information(this,tr("Settings saved"),tr("Your upload info & settings are saved!"));
	} else {
		QMessageBox::warning(this,tr("Settings save error"),this->upl->api->last_error);
	}
	this->btnStateSave(false);
	this->ui->grUploaded->setDisabled(false);
}

void ui_upload::on_btnDelete_clicked()
{
	if (QMessageBox::Yes != QMessageBox::question(this,tr("Delete upload?"),tr("Are you sure what you want to DELETE this upload?"),QMessageBox::Yes,QMessageBox::No))
		return;
	this->btnStateDelete(true);
	this->ui->grUploaded->setDisabled(true);

	if (this->upl->deleteMe())
	{
		QMessageBox::information(this,tr("Upload deleted"),tr("Your upload was deleted!"));
		this->close();
		this->deleteLater();
	} else {
		QMessageBox::warning(this,tr("Deleteion error"),this->upl->api->last_error);
		this->btnStateDelete(false);
		this->ui->grUploaded->setDisabled(false);
	}
	core->reload_ui();
 }

void ui_upload::on_btnCancel_clicked()
{
	int res = QMessageBox::question(this,tr("Stop upload?"),tr("Are you shure to sop this uploading?"),QMessageBox::Yes,QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		// Stop the war...
		this->ui->btnCancel->setDisabled(true);
		// this->upl->deleteMe(true);
	}
}
