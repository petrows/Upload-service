
QT += core gui widgets network xml

# Include Qt-Single-App:
include (3dpatry/qtsingleapplication/src/qtsingleapplication.pri)

# Include zip library:
DEFINES += QUAZIP_BUILD
DEFINES += QUAZIP_STATIC

DEFINES += ENABLE_ZIP

unix {
	LIBS += -lz
}
macx {
	LIBS += -lz
}
win32 {
        LIBS += -L"$$PWD/3dpatry/zlib-win32/" -lzlib1 "$$PWD/3dpatry/zlib-win32/zdll.lib"
        INCLUDEPATH += 3dpatry/zlib-win32/include/
}
include (3dpatry/quazip/quazip.pri)


DESTDIR = ./build/

# Define vars per-platform build:
unix:DESTDIR  = ./build/unix
win32:DESTDIR = ./build/win32
macx:DESTDIR  = ./build/macx

unix = upload-client
win32|macx:TARGET = Upload

TRANSLATIONS += lang/ru.ts

# Build env:
OBJECTS_DIR = ./tmp/
MOC_DIR     = ./tmp/
UI_DIR      = ./tmp/

SOURCES += \
	src/main.cpp \
	src/u_core.cpp \
	src/ui_main.cpp \
	src/ui_wdg_ulist.cpp \
	src/u_upload.cpp \
	src/ui_upload.cpp \
	src/ui_settings.cpp \
	src/ui_init.cpp \
	src/u_api.cpp \
	src/md5.cpp \
	src/ui_wdg_flist.cpp \
	src/ui_wdg_btnlabel.cpp \
	src/u_update.cpp \
	src/ui_update.cpp \
	src/ui_askwindow.cpp \
	src/u_common.cpp \
	src/ui_zip_files.cpp \
	src/ui_about.cpp \
	src/qaskwnd.cpp

HEADERS += \
	src/global.h \
	src/u_core.h \
	src/ui_main.h \
	src/ui_wdg_ulist.h \
	src/u_upload.h \
	src/ui_upload.h \
	src/ui_settings.h \
	src/ui_init.h \
	src/u_api.h \
	src/md5.h \
	src/version.h \
	src/ui_wdg_flist.h \
	src/ui_wdg_btnlabel.h \
	src/u_update.h \
	src/ui_update.h \
	src/ui_askwindow.h \
	src/u_common.h \
	src/ui_zip_files.h \
	src/ui_about.h \
	src/qaskwnd.h

FORMS += \
	src/ui_main.ui \
	src/ui_upload.ui \
	src/ui_settings.ui \
	src/ui_init.ui \
	src/ui_update.ui \
	src/ui_askwindow.ui \
	src/ui_zip_files.ui \
	src/ui_about.ui

RESOURCES += \
	lang/lang.qrc \
	res/res.qrc

OTHER_FILES += \
	res/app.rc

# App icon resourses
win32:RC_FILE = res/app.rc
macx:RC_FILE  = res/db_commit.icns























