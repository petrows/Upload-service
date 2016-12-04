/********************************************************************************
** Form generated from reading UI file 'ui_zip_files.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_ZIP_FILES_H
#define UI_UI_ZIP_FILES_H

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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ui_zip_files
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *lblFiles;
    QLabel *label_2;
    QLabel *lblArchSize;
    QLabel *label_3;
    QLabel *label_4;
    QProgressBar *prgrFile;
    QLabel *lblFile;
    QLabel *label_5;
    QFrame *line;
    QFrame *line_2;
    QProgressBar *prgrTotal;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ui_zip_files)
    {
        if (ui_zip_files->objectName().isEmpty())
            ui_zip_files->setObjectName(QStringLiteral("ui_zip_files"));
        ui_zip_files->resize(474, 194);
        verticalLayout = new QVBoxLayout(ui_zip_files);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label = new QLabel(ui_zip_files);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lblFiles = new QLabel(ui_zip_files);
        lblFiles->setObjectName(QStringLiteral("lblFiles"));
        lblFiles->setText(QStringLiteral("?"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblFiles);

        label_2 = new QLabel(ui_zip_files);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lblArchSize = new QLabel(ui_zip_files);
        lblArchSize->setObjectName(QStringLiteral("lblArchSize"));
        lblArchSize->setText(QStringLiteral("?"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblArchSize);

        label_3 = new QLabel(ui_zip_files);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(ui_zip_files);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        prgrFile = new QProgressBar(ui_zip_files);
        prgrFile->setObjectName(QStringLiteral("prgrFile"));
        prgrFile->setValue(0);

        formLayout->setWidget(4, QFormLayout::FieldRole, prgrFile);

        lblFile = new QLabel(ui_zip_files);
        lblFile->setObjectName(QStringLiteral("lblFile"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblFile->sizePolicy().hasHeightForWidth());
        lblFile->setSizePolicy(sizePolicy);
        lblFile->setText(QStringLiteral("?"));
        lblFile->setTextFormat(Qt::PlainText);

        formLayout->setWidget(3, QFormLayout::FieldRole, lblFile);

        label_5 = new QLabel(ui_zip_files);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_5);

        line = new QFrame(ui_zip_files);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(100, 0));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(5, QFormLayout::FieldRole, line);

        line_2 = new QFrame(ui_zip_files);
        line_2->setObjectName(QStringLiteral("line_2"));
        sizePolicy1.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy1);
        line_2->setMinimumSize(QSize(100, 0));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        formLayout->setWidget(2, QFormLayout::FieldRole, line_2);

        prgrTotal = new QProgressBar(ui_zip_files);
        prgrTotal->setObjectName(QStringLiteral("prgrTotal"));
        prgrTotal->setValue(0);

        formLayout->setWidget(6, QFormLayout::FieldRole, prgrTotal);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCancel = new QPushButton(ui_zip_files);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/cross"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon);

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ui_zip_files);

        QMetaObject::connectSlotsByName(ui_zip_files);
    } // setupUi

    void retranslateUi(QDialog *ui_zip_files)
    {
        ui_zip_files->setWindowTitle(QApplication::translate("ui_zip_files", "Compressing files...", 0));
        label->setText(QApplication::translate("ui_zip_files", "FIles:", 0));
        label_2->setText(QApplication::translate("ui_zip_files", "Archive size:", 0));
        label_3->setText(QApplication::translate("ui_zip_files", "File:", 0));
        label_4->setText(QApplication::translate("ui_zip_files", "Progress:", 0));
        label_5->setText(QApplication::translate("ui_zip_files", "Total:", 0));
        btnCancel->setText(QApplication::translate("ui_zip_files", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_zip_files: public Ui_ui_zip_files {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_ZIP_FILES_H
