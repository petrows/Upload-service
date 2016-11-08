#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QtWidgets/QApplication>
#include <QSettings>
#include <QDir>
#include <QUrl>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTime>
#include <QtWidgets/QFileDialog>
#include <QThread>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressBar>
#include <QDomDocument>
#include <QIcon>
#include <QDebug>

#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "version.h"

#define UPLOAD_DOMAIN "upload.petro.selan"

class u_api;
class u_core;
class u_upload;
class u_update;
class ui_init;
class ui_main;
class ui_upload;
class ui_settings;
class ui_update;
class ui_wdg_ulist;
class ui_wdg_flist;
class ui_wdg_btnlabel;

#ifndef IN_MAIN
extern u_core * core;
#else
u_core * core;
#endif

#endif // GLOBAL_H
