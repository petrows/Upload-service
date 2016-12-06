#include "u_common.h"

#include <QDebug>
#include <QUrlQuery>

#ifdef USE_ZIP

zip_pack::zip_pack(QObject *parent) : QObject(parent) {
	this->unlink_on_exit = true;
	this->zip_out = QDir::tempPath() + QString().sprintf("/up-zip-%d.tmp", qrand());
	this->zp = new QuaZip(this->zip_out);
}
zip_pack::~zip_pack() {
	if (this->zip_out.length() && this->unlink_on_exit) {
		QFile::remove(this->zip_out);
	}
}

bool zip_pack::pack_files(QStringList files) {
	for (int x = 0; x < files.count(); x++) {
		QFileInfo fi(files.at(x));
		QString fname = fi.fileName();
		QString froot = fi.dir().canonicalPath();
		this->sc_files(froot, fname);
	}

	this->_fc_total = this->files_in.count();
	this->_fc_done = 0;

	emit this->started();

	QFile::remove(this->zip_out);

	if (!this->zp->open(QuaZip::mdCreate)) {
		this->last_error = tr("Enable to create archive '%1'!").arg(this->zip_out);
		emit this->error(this->last_error);
		return false;
	}

	for (int x = 0; x < this->files_in.count(); x++) {
		this->_fc_done++;
		emit this->file_started(this->files_in.at(x).first, this->files_in.at(x).second);

		// Open file!
		QFile file_in(this->files_in.at(x).first + "/" + this->files_in.at(x).second);
		QFileInfo file_in_inf(this->files_in.at(x).first + "/" + this->files_in.at(x).second);
		if (!file_in.open(QIODevice::ReadOnly)) {
			this->last_error = tr("Enable to read file '%1'!").arg(this->files_in.at(x).first + "/" + this->files_in.at(x).second);
			emit this->error(this->last_error);
			return false;
		}

		QuaZipFile flz(this->zp);
		QuaZipNewInfo fni(this->files_in.at(x).second, this->files_in.at(x).first + "/" + this->files_in.at(x).second);
		// quint32 perms = 0x00000000 + (file_in_inf.permissions());
		// perms = perms << 16;

		// fni.externalAttr = 0777 << 16L;
		fni.externalAttr = perms_hex2oct(file_in_inf.permissions()) << 16L;
		if (!flz.open(QIODevice::WriteOnly, fni))
			continue;

		qint64 file_in_size = file_in.bytesAvailable();
		qint64 file_in_done = 0;

		char in_buf[10240];
		while (file_in.bytesAvailable()) {
			qint64 readb = file_in.read(in_buf, 10240);
			if (readb <= 0)
				break;
			file_in_done += readb;
			flz.write(in_buf, readb);
			emit this->file_progress(file_in_done, file_in_size);
			QApplication::processEvents();
		}
		flz.close();

		emit this->file_added(this->files_in.at(x).first, this->files_in.at(x).second);
	}

	this->zp->close();

	emit this->finished();

	return true;
}

void zip_pack::sc_files(QString root, QString fname) {
	qDebug() << "sc: " << root << " : " << fname;
	QFileInfo fi(root + "/" + fname);
	if (fi.isDir()) {
		if (fname.length()) {
			// this->files_in << qMakePair(root,fname + "/");
		}
		// Scan sub-dirs
		QDir dr(root + "/" + fname);
		QStringList dr_data = dr.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
		if (fname.length())
			fname += "/";
		for (int x = 0; x < dr_data.count(); x++) {
			this->sc_files(root, fname + dr_data.at(x));
		}

		return;
	}

	// File - add it
	this->files_in << qMakePair(root, fname);
}

int zip_pack::files_done() { return this->_fc_done; }
int zip_pack::files_total() { return this->_fc_total; }
qint64 zip_pack::zip_size() {
	QFileInfo zsize(this->zip_out);
	return zsize.size();
}

#endif // USE_ZIP

quint32 perms_hex2oct(quint32 phex) {
	phex = phex & 0x0FFF;
	char buf_in[16];
	sprintf(buf_in, "%x", phex);
	return QString(buf_in).toInt(NULL, 8);
}
