/********************************************************************************
** Form generated from reading UI file 'ui_main.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_MAIN_H
#define UI_UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ui_main
{
public:
    QAction *actionHide;
    QAction *actionExit;
    QAction *actionNew_upload;
    QAction *actionSettings;
    QAction *actionUpdatesMenu;
    QAction *actionAbout_program;
    QAction *actionHome_page;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *layoutList;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClipUpload;
    QPushButton *btnNewUpload;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuUpload;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ui_main)
    {
        if (ui_main->objectName().isEmpty())
            ui_main->setObjectName(QStringLiteral("ui_main"));
        ui_main->resize(800, 600);
        ui_main->setAcceptDrops(true);
        actionHide = new QAction(ui_main);
        actionHide->setObjectName(QStringLiteral("actionHide"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/arrow-315"), QSize(), QIcon::Normal, QIcon::Off);
        actionHide->setIcon(icon);
        actionExit = new QAction(ui_main);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/cross-button"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionNew_upload = new QAction(ui_main);
        actionNew_upload->setObjectName(QStringLiteral("actionNew_upload"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/up"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_upload->setIcon(icon2);
        actionSettings = new QAction(ui_main);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/hammer-screwdriver"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon3);
        actionUpdatesMenu = new QAction(ui_main);
        actionUpdatesMenu->setObjectName(QStringLiteral("actionUpdatesMenu"));
        actionUpdatesMenu->setText(QStringLiteral("&updatesMenu"));
        actionAbout_program = new QAction(ui_main);
        actionAbout_program->setObjectName(QStringLiteral("actionAbout_program"));
        actionHome_page = new QAction(ui_main);
        actionHome_page->setObjectName(QStringLiteral("actionHome_page"));
        actionAbout_Qt = new QAction(ui_main);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(ui_main);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        layoutList = new QVBoxLayout();
        layoutList->setObjectName(QStringLiteral("layoutList"));

        verticalLayout->addLayout(layoutList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClipUpload = new QPushButton(centralwidget);
        btnClipUpload->setObjectName(QStringLiteral("btnClipUpload"));
        btnClipUpload->setIcon(icon2);

        horizontalLayout->addWidget(btnClipUpload);

        btnNewUpload = new QPushButton(centralwidget);
        btnNewUpload->setObjectName(QStringLiteral("btnNewUpload"));
        btnNewUpload->setIcon(icon2);

        horizontalLayout->addWidget(btnNewUpload);


        verticalLayout->addLayout(horizontalLayout);

        ui_main->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ui_main);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuUpload = new QMenu(menubar);
        menuUpload->setObjectName(QStringLiteral("menuUpload"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        ui_main->setMenuBar(menubar);
        statusbar = new QStatusBar(ui_main);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ui_main->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuUpload->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionSettings);
        menuFile->addAction(actionHide);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuUpload->addAction(actionNew_upload);
        menuAbout->addAction(actionUpdatesMenu);
        menuAbout->addAction(actionAbout_program);
        menuAbout->addAction(actionHome_page);
        menuAbout->addAction(actionAbout_Qt);

        retranslateUi(ui_main);

        QMetaObject::connectSlotsByName(ui_main);
    } // setupUi

    void retranslateUi(QMainWindow *ui_main)
    {
        ui_main->setWindowTitle(QApplication::translate("ui_main", "MainWindow", 0));
        actionHide->setText(QApplication::translate("ui_main", "&Hide", 0));
        actionExit->setText(QApplication::translate("ui_main", "&Exit", 0));
        actionNew_upload->setText(QApplication::translate("ui_main", "&New upload...", 0));
        actionSettings->setText(QApplication::translate("ui_main", "&Settings...", 0));
        actionAbout_program->setText(QApplication::translate("ui_main", "&About program...", 0));
        actionHome_page->setText(QApplication::translate("ui_main", "&Home page", 0));
        actionAbout_Qt->setText(QApplication::translate("ui_main", "About &Qt...", 0));
        btnClipUpload->setText(QApplication::translate("ui_main", "Clipboard", 0));
        btnClipUpload->setShortcut(QApplication::translate("ui_main", "Ctrl+V", 0));
        btnNewUpload->setText(QApplication::translate("ui_main", "File", 0));
        menuFile->setTitle(QApplication::translate("ui_main", "&File", 0));
        menuUpload->setTitle(QApplication::translate("ui_main", "&Upload", 0));
        menuAbout->setTitle(QApplication::translate("ui_main", "A&bout", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_main: public Ui_ui_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_MAIN_H
