/********************************************************************************
** Form generated from reading UI file 'ui_askwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_ASKWINDOW_H
#define UI_UI_ASKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ui_askwindow
{
public:

    void setupUi(QDialog *ui_askwindow)
    {
        if (ui_askwindow->objectName().isEmpty())
            ui_askwindow->setObjectName(QStringLiteral("ui_askwindow"));
        ui_askwindow->resize(400, 300);

        retranslateUi(ui_askwindow);

        QMetaObject::connectSlotsByName(ui_askwindow);
    } // setupUi

    void retranslateUi(QDialog *ui_askwindow)
    {
        ui_askwindow->setWindowTitle(QApplication::translate("ui_askwindow", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_askwindow: public Ui_ui_askwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_ASKWINDOW_H
