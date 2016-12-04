/********************************************************************************
** Form generated from reading UI file 'ui_upload.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_UPLOAD_H
#define UI_UI_UPLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ui_upload
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *grUpload;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *lblUplSize;
    QLabel *lblUplSpeed;
    QProgressBar *prTotal;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *grUploaded;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QLabel *label_6;
    QLineEdit *edtDescr;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *boxTtl;
    QCheckBox *chRenew;
    QLabel *label;
    QLabel *lblPublicLink;
    QLabel *label_2;
    QLabel *lblTtl;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSave;
    QPushButton *btnDelete;
    QVBoxLayout *layoutFiles;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ui_upload)
    {
        if (ui_upload->objectName().isEmpty())
            ui_upload->setObjectName(QStringLiteral("ui_upload"));
        ui_upload->resize(600, 500);
        verticalLayout = new QVBoxLayout(ui_upload);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        grUpload = new QGroupBox(ui_upload);
        grUpload->setObjectName(QStringLiteral("grUpload"));
        verticalLayout_2 = new QVBoxLayout(grUpload);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_4 = new QLabel(grUpload);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(grUpload);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        lblUplSize = new QLabel(grUpload);
        lblUplSize->setObjectName(QStringLiteral("lblUplSize"));
        lblUplSize->setText(QStringLiteral("?"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lblUplSize);

        lblUplSpeed = new QLabel(grUpload);
        lblUplSpeed->setObjectName(QStringLiteral("lblUplSpeed"));
        lblUplSpeed->setText(QStringLiteral("?"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lblUplSpeed);


        verticalLayout_2->addLayout(formLayout_2);

        prTotal = new QProgressBar(grUpload);
        prTotal->setObjectName(QStringLiteral("prTotal"));
        prTotal->setValue(0);

        verticalLayout_2->addWidget(prTotal);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btnCancel = new QPushButton(grUpload);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/cross"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon);

        horizontalLayout_3->addWidget(btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(grUpload);

        grUploaded = new QGroupBox(ui_upload);
        grUploaded->setObjectName(QStringLiteral("grUploaded"));
        verticalLayout_3 = new QVBoxLayout(grUploaded);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label_7 = new QLabel(grUploaded);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_7);

        label_6 = new QLabel(grUploaded);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_6);

        edtDescr = new QLineEdit(grUploaded);
        edtDescr->setObjectName(QStringLiteral("edtDescr"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, edtDescr);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        boxTtl = new QComboBox(grUploaded);
        boxTtl->setObjectName(QStringLiteral("boxTtl"));

        horizontalLayout_2->addWidget(boxTtl);

        chRenew = new QCheckBox(grUploaded);
        chRenew->setObjectName(QStringLiteral("chRenew"));

        horizontalLayout_2->addWidget(chRenew);


        formLayout_3->setLayout(3, QFormLayout::FieldRole, horizontalLayout_2);

        label = new QLabel(grUploaded);
        label->setObjectName(QStringLiteral("label"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label);

        lblPublicLink = new QLabel(grUploaded);
        lblPublicLink->setObjectName(QStringLiteral("lblPublicLink"));
        lblPublicLink->setText(QStringLiteral("-"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lblPublicLink);

        label_2 = new QLabel(grUploaded);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_2);

        lblTtl = new QLabel(grUploaded);
        lblTtl->setObjectName(QStringLiteral("lblTtl"));
        lblTtl->setText(QStringLiteral("?"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lblTtl);


        verticalLayout_3->addLayout(formLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnSave = new QPushButton(grUploaded);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setText(QStringLiteral("Save"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/tick"), QSize(), QIcon::Normal, QIcon::Off);
        btnSave->setIcon(icon1);

        horizontalLayout->addWidget(btnSave);

        btnDelete = new QPushButton(grUploaded);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setText(QStringLiteral("Delete"));
        btnDelete->setIcon(icon);

        horizontalLayout->addWidget(btnDelete);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout->addWidget(grUploaded);

        layoutFiles = new QVBoxLayout();
        layoutFiles->setObjectName(QStringLiteral("layoutFiles"));

        verticalLayout->addLayout(layoutFiles);

        buttonBox = new QDialogButtonBox(ui_upload);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ui_upload);
        QObject::connect(buttonBox, SIGNAL(accepted()), ui_upload, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ui_upload, SLOT(reject()));

        QMetaObject::connectSlotsByName(ui_upload);
    } // setupUi

    void retranslateUi(QDialog *ui_upload)
    {
        ui_upload->setWindowTitle(QApplication::translate("ui_upload", "Dialog", 0));
        grUpload->setTitle(QApplication::translate("ui_upload", "Uploading...", 0));
        label_4->setText(QApplication::translate("ui_upload", "Data uploaded:", 0));
        label_5->setText(QApplication::translate("ui_upload", "Avg. speed:", 0));
        btnCancel->setText(QApplication::translate("ui_upload", "Cancel", 0));
        grUploaded->setTitle(QApplication::translate("ui_upload", "Upload settings", 0));
        label_7->setText(QApplication::translate("ui_upload", "Description:", 0));
        label_6->setText(QApplication::translate("ui_upload", "Storage time:", 0));
        chRenew->setText(QApplication::translate("ui_upload", "Renew storage time after next download", 0));
        label->setText(QApplication::translate("ui_upload", "Public link:", 0));
        label_2->setText(QApplication::translate("ui_upload", "Time-to-live:", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_upload: public Ui_ui_upload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_UPLOAD_H
