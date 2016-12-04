/********************************************************************************
** Form generated from reading UI file 'ui_about.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_ABOUT_H
#define UI_UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ui_about
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *line;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *lblVersion;
    QLabel *label_3;
    QLabel *lblBuildDate;
    QFrame *line_2;
    QLabel *lblOwner;
    QFrame *line_3;
    QLabel *label_5;
    QLabel *lblIconPacks;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;

    void setupUi(QDialog *ui_about)
    {
        if (ui_about->objectName().isEmpty())
            ui_about->setObjectName(QStringLiteral("ui_about"));
        ui_about->setWindowModality(Qt::ApplicationModal);
        ui_about->resize(400, 300);
        verticalLayout = new QVBoxLayout(ui_about);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ui_about);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        line = new QFrame(ui_about);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(ui_about);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        lblVersion = new QLabel(ui_about);
        lblVersion->setObjectName(QStringLiteral("lblVersion"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lblVersion->setFont(font);
        lblVersion->setText(QStringLiteral("?"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblVersion);

        label_3 = new QLabel(ui_about);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        lblBuildDate = new QLabel(ui_about);
        lblBuildDate->setObjectName(QStringLiteral("lblBuildDate"));
        lblBuildDate->setText(QStringLiteral("?"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblBuildDate);


        verticalLayout->addLayout(formLayout);

        line_2 = new QFrame(ui_about);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        lblOwner = new QLabel(ui_about);
        lblOwner->setObjectName(QStringLiteral("lblOwner"));

        verticalLayout->addWidget(lblOwner);

        line_3 = new QFrame(ui_about);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        label_5 = new QLabel(ui_about);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        lblIconPacks = new QLabel(ui_about);
        lblIconPacks->setObjectName(QStringLiteral("lblIconPacks"));
        lblIconPacks->setText(QLatin1String("<ul>\n"
"<li><a href=\"http://p.yusukekamiyamane.com/\">Fugue Icons package</a>.</li>\n"
"<li><a href=\"http://www.oxygen-icons.org/\">Oxygen icons theme</a>.</li>\n"
"<li><a href=\"http://www.everaldo.com/\">Crystal</a> by Everaldo Coelho.</li>\n"
"</ul>"));

        verticalLayout->addWidget(lblIconPacks);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(ui_about);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/cross"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ui_about);

        QMetaObject::connectSlotsByName(ui_about);
    } // setupUi

    void retranslateUi(QDialog *ui_about)
    {
        ui_about->setWindowTitle(QApplication::translate("ui_about", "About program", 0));
        label->setText(QApplication::translate("ui_about", "<h2>U.PETRO.WS upload client</h2>", 0));
        label_2->setText(QApplication::translate("ui_about", "Version:", 0));
        label_3->setText(QApplication::translate("ui_about", "Builded:", 0));
        lblOwner->setText(QApplication::translate("ui_about", "<center>Production of <a href=\"http://www.petro.ws/\"><b>petro.ws</b></a>.", 0));
        label_5->setText(QApplication::translate("ui_about", "Used icons packs in program:", 0));
        btnClose->setText(QApplication::translate("ui_about", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_about: public Ui_ui_about {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_ABOUT_H
