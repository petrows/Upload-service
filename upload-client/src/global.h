#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <QDir>
#include <QDomDocument>
#include <QIcon>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSettings>
#include <QThread>
#include <QTime>
#include <QUrl>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressBar>

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "version.h"

#define UPLOAD_DOMAIN "u.petro.ws"
//#define UPLOAD_DOMAIN "upload.petro.selan"

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
extern u_core *core;
#else
u_core *core;
#endif

#endif // GLOBAL_H
