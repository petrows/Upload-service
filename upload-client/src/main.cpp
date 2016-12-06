#define IN_MAIN

#include "global.h"
#include "u_common.h"
#include "u_core.h"
#include <QTranslator>
#include <QtSingleApplication>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QtSingleApplication a(argc, argv);

	Q_INIT_RESOURCE(res);

	qsrand(QDateTime::currentDateTime().toTime_t());

	a.setApplicationName("u-petro-ws-uploader");
	a.setOrganizationName("kedr.inc");
	a.setWindowIcon(QIcon(":/icons/db_commit.ico"));

	a.setQuitOnLastWindowClosed(false);

	// QMessageBox::information(0,"",QApplication::arguments().join(", "));

	if (QApplication::arguments().contains("--update-mode") || QApplication::arguments().contains("--clean")) {
		// 'Update' mode
		// a.sendMessage("exit");
	} else {
		if (argc == 1) {
			// No args: just show window
			if (a.sendMessage("show"))
				return 2;
		} else {
			// Send new uploads string
			QStringList args = QApplication::arguments();
			QStringList args_out;
			for (int x = 1; x < args.count(); x++) {
				QFileInfo inf(args.at(x));

				if (!inf.isReadable())
					continue;
				args_out.append(inf.absoluteFilePath());
			}
			if (a.sendMessage(args_out.join("\n")))
				return 0;
		}
	}

	QTranslator trans;
	trans.load(":/lang/" + QLocale::system().name());
	a.installTranslator(&trans);

	core = new u_core();
	QObject::connect(&a, SIGNAL(messageReceived(QString)), core, SLOT(qsa_message(QString)));
	core->run();

	return a.exec();
}
