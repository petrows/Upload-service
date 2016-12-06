#include "ui_zip_files.h"
#include "ui_ui_zip_files.h"

#include "global.h"
#include "u_core.h"

ui_zip_files::ui_zip_files(QWidget *parent) : QDialog(parent), ui(new Ui::ui_zip_files) {
	ui->setupUi(this);

	this->zip.unlink_on_exit = false;

	connect(&this->zip, SIGNAL(file_started(QString, QString)), SLOT(file_started(QString, QString)));
	connect(&this->zip, SIGNAL(file_progress(qint64, qint64)), SLOT(file_progress(qint64, qint64)));
	// connect(&this->zip,SIGNAL(finished()),SLOT(finished()));
	connect(&this->zip, SIGNAL(error(QString)), SLOT(z_error(QString)));
}

ui_zip_files::~ui_zip_files() { delete ui; }

bool ui_zip_files::start_files(QStringList in) {
	this->ui->lblFiles->setText(tr("Scanning files..."));
	// Okay, run!
	if (!zip.pack_files(in))
		return false;
	this->finished();
	return true;
}

void ui_zip_files::pack_started() {}

void ui_zip_files::file_started(QString /*file*/, QString name) {
	this->ui->lblFile->setText(name);
	this->ui->lblFiles->setText(QString("%1 / %2").arg(zip.files_done()).arg(zip.files_total()));

	int progr = ((double)zip.files_done() / (double)zip.files_total()) * 100.00;
	this->ui->prgrTotal->setValue(progr);
}

void ui_zip_files::file_progress(qint64 done, qint64 total) {
	int progr = ((long double)done / (long double)total) * 100.00;
	this->ui->prgrFile->setValue(progr);
	this->ui->lblArchSize->setText(u_core::format_size(zip.zip_size()));
}

void ui_zip_files::finished() {
	// All done!
	QStringList fls;
	fls << this->zip.zip_out;

	// Get first file name
	QFileInfo fni(this->zip.files_in.at(0).second);
	QString tmp_dir = QDir::tempPath();
	QString fname_in = fni.baseName();
	QString fname_out = fname_in + ".zip";
	QFileInfo fino(tmp_dir + "/" + fname_out);
	int fcnts = 0;
	while (fino.exists()) {
		fcnts++;
		fname_out = fname_in + " (" + QString::number(fcnts) + ")" + ".zip";
		fino.setFile(tmp_dir + "/" + fname_out);
	}

	this->zip_out = tmp_dir + "/" + fname_out;
	QFile::rename(this->zip.zip_out, this->zip_out);

	this->close();
}

void ui_zip_files::z_error(QString text) {
	QMessageBox::warning(this, tr("Compress error!"), text);
	this->close();
}
