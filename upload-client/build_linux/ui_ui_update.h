/********************************************************************************
** Form generated from reading UI file 'ui_update.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_UPDATE_H
#define UI_UI_UPDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ui_update
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QLabel *lblStatus;
    QProgressBar *progrMain;
    QTextBrowser *txtDetails;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnUpdate;
    QPushButton *btnCancel;

    void setupUi(QDialog *ui_update)
    {
        if (ui_update->objectName().isEmpty())
            ui_update->setObjectName(QStringLiteral("ui_update"));
        ui_update->resize(450, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ui_update->sizePolicy().hasHeightForWidth());
        ui_update->setSizePolicy(sizePolicy);
        ui_update->setMinimumSize(QSize(450, 300));
        ui_update->setMaximumSize(QSize(450, 300));
        verticalLayout_2 = new QVBoxLayout(ui_update);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(ui_update);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        line = new QFrame(ui_update);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lblStatus = new QLabel(ui_update);
        lblStatus->setObjectName(QStringLiteral("lblStatus"));
        lblStatus->setText(QStringLiteral("?"));

        verticalLayout->addWidget(lblStatus);

        progrMain = new QProgressBar(ui_update);
        progrMain->setObjectName(QStringLiteral("progrMain"));
        progrMain->setValue(0);

        verticalLayout->addWidget(progrMain);


        verticalLayout_2->addLayout(verticalLayout);

        txtDetails = new QTextBrowser(ui_update);
        txtDetails->setObjectName(QStringLiteral("txtDetails"));
        txtDetails->setEnabled(false);
        txtDetails->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Verdana'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif';\"></p></body></html>"));

        verticalLayout_2->addWidget(txtDetails);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnUpdate = new QPushButton(ui_update);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));
        btnUpdate->setEnabled(false);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        btnUpdate->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/tick"), QSize(), QIcon::Normal, QIcon::Off);
        btnUpdate->setIcon(icon);
        btnUpdate->setAutoDefault(true);

        horizontalLayout->addWidget(btnUpdate);

        btnCancel = new QPushButton(ui_update);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/cross"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon1);
        btnCancel->setAutoDefault(false);

        horizontalLayout->addWidget(btnCancel);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ui_update);

        btnUpdate->setDefault(true);


        QMetaObject::connectSlotsByName(ui_update);
    } // setupUi

    void retranslateUi(QDialog *ui_update)
    {
        ui_update->setWindowTitle(QApplication::translate("ui_update", "Updating client", 0));
        label->setText(QApplication::translate("ui_update", "<p>Client <b>u.petro.ws</b> is updating to the newest version.</p>", 0));
        btnUpdate->setText(QApplication::translate("ui_update", "Update", 0));
        btnCancel->setText(QApplication::translate("ui_update", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_update: public Ui_ui_update {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_UPDATE_H
