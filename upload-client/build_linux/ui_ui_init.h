/********************************************************************************
** Form generated from reading UI file 'ui_init.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_INIT_H
#define UI_UI_INIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ui_init
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ui_init)
    {
        if (ui_init->objectName().isEmpty())
            ui_init->setObjectName(QStringLiteral("ui_init"));
        ui_init->resize(400, 100);
        ui_init->setMinimumSize(QSize(400, 100));
        ui_init->setMaximumSize(QSize(400, 100));
        verticalLayout = new QVBoxLayout(ui_init);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ui_init);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCancel = new QPushButton(ui_init);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/cross"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon);

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ui_init);

        QMetaObject::connectSlotsByName(ui_init);
    } // setupUi

    void retranslateUi(QDialog *ui_init)
    {
        ui_init->setWindowTitle(QApplication::translate("ui_init", "u.petro.ws: Init session", 0));
        label->setText(QApplication::translate("ui_init", "Please wait, starting program session...", 0));
        btnCancel->setText(QApplication::translate("ui_init", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_init: public Ui_ui_init {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_INIT_H
