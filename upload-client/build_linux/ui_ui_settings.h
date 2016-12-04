/********************************************************************************
** Form generated from reading UI file 'ui_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_SETTINGS_H
#define UI_UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ui_settings
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *edtLogin;
    QLineEdit *edtPassword;
    QPushButton *btnCheck;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *boxUpdPeriod;
    QLabel *label_5;
    QFrame *line;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *rbtZipAsk;
    QRadioButton *rbtZipAlways;
    QRadioButton *rbtZipNever;
    QWidget *tabNetwork;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *grpProxy;
    QFormLayout *formLayout_3;
    QLabel *label_6;
    QComboBox *boxProxyType;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *edtProxyIp;
    QSpinBox *edtProxyPort;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *ui_settings)
    {
        if (ui_settings->objectName().isEmpty())
            ui_settings->setObjectName(QStringLiteral("ui_settings"));
        ui_settings->setWindowModality(Qt::ApplicationModal);
        ui_settings->resize(488, 401);
        verticalLayout = new QVBoxLayout(ui_settings);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(ui_settings);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QStringLiteral("tabGeneral"));
        verticalLayout_3 = new QVBoxLayout(tabGeneral);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(tabGeneral);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setContentsMargins(0, -1, -1, -1);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(150, 0));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        edtLogin = new QLineEdit(groupBox);
        edtLogin->setObjectName(QStringLiteral("edtLogin"));
        edtLogin->setMaximumSize(QSize(200, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, edtLogin);

        edtPassword = new QLineEdit(groupBox);
        edtPassword->setObjectName(QStringLiteral("edtPassword"));
        edtPassword->setMaximumSize(QSize(200, 16777215));
        edtPassword->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, edtPassword);

        btnCheck = new QPushButton(groupBox);
        btnCheck->setObjectName(QStringLiteral("btnCheck"));
        btnCheck->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, btnCheck);


        verticalLayout_2->addLayout(formLayout);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tabGeneral);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(150, 0));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        boxUpdPeriod = new QComboBox(groupBox_2);
        boxUpdPeriod->setObjectName(QStringLiteral("boxUpdPeriod"));

        horizontalLayout_4->addWidget(boxUpdPeriod);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout_4);

        line = new QFrame(groupBox_2);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMinimumSize(QSize(100, 0));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, line);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        rbtZipAsk = new QRadioButton(groupBox_2);
        rbtZipAsk->setObjectName(QStringLiteral("rbtZipAsk"));

        verticalLayout_5->addWidget(rbtZipAsk);

        rbtZipAlways = new QRadioButton(groupBox_2);
        rbtZipAlways->setObjectName(QStringLiteral("rbtZipAlways"));

        verticalLayout_5->addWidget(rbtZipAlways);

        rbtZipNever = new QRadioButton(groupBox_2);
        rbtZipNever->setObjectName(QStringLiteral("rbtZipNever"));

        verticalLayout_5->addWidget(rbtZipNever);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, verticalLayout_5);


        verticalLayout_3->addWidget(groupBox_2);

        tabWidget->addTab(tabGeneral, QString());
        tabNetwork = new QWidget();
        tabNetwork->setObjectName(QStringLiteral("tabNetwork"));
        verticalLayout_4 = new QVBoxLayout(tabNetwork);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        grpProxy = new QGroupBox(tabNetwork);
        grpProxy->setObjectName(QStringLiteral("grpProxy"));
        grpProxy->setCheckable(true);
        grpProxy->setChecked(false);
        formLayout_3 = new QFormLayout(grpProxy);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_6 = new QLabel(grpProxy);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(150, 0));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_6);

        boxProxyType = new QComboBox(grpProxy);
        boxProxyType->setObjectName(QStringLiteral("boxProxyType"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, boxProxyType);

        label_7 = new QLabel(grpProxy);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(grpProxy);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_8);

        edtProxyIp = new QLineEdit(grpProxy);
        edtProxyIp->setObjectName(QStringLiteral("edtProxyIp"));
        edtProxyIp->setMaximumSize(QSize(200, 16777215));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, edtProxyIp);

        edtProxyPort = new QSpinBox(grpProxy);
        edtProxyPort->setObjectName(QStringLiteral("edtProxyPort"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, edtProxyPort);


        verticalLayout_4->addWidget(grpProxy);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        tabWidget->addTab(tabNetwork, QString());

        verticalLayout->addWidget(tabWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(ui_settings);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/tick"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon);

        horizontalLayout->addWidget(btnOk);

        btnCancel = new QPushButton(ui_settings);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/cross"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon1);

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ui_settings);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ui_settings);
    } // setupUi

    void retranslateUi(QDialog *ui_settings)
    {
        ui_settings->setWindowTitle(QApplication::translate("ui_settings", "Options", 0));
        groupBox->setTitle(QApplication::translate("ui_settings", "Account settings", 0));
        label->setText(QApplication::translate("ui_settings", "Login / E-mail:", 0));
        label_2->setText(QApplication::translate("ui_settings", "Password:", 0));
        btnCheck->setText(QApplication::translate("ui_settings", "Check", 0));
        groupBox_2->setTitle(QApplication::translate("ui_settings", "Common", 0));
        label_3->setText(QApplication::translate("ui_settings", "Show me updates:", 0));
        label_5->setText(QApplication::translate("ui_settings", "... if avaliable.", 0));
        label_4->setText(QApplication::translate("ui_settings", "Zip when many files:", 0));
        rbtZipAsk->setText(QApplication::translate("ui_settings", "Ask me everytime", 0));
        rbtZipAlways->setText(QApplication::translate("ui_settings", "Always compress if group of files.", 0));
        rbtZipNever->setText(QApplication::translate("ui_settings", "Never promt zip compression.", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QApplication::translate("ui_settings", "General", 0));
        grpProxy->setTitle(QApplication::translate("ui_settings", "Use proxy?", 0));
        label_6->setText(QApplication::translate("ui_settings", "Proxy type:", 0));
        label_7->setText(QApplication::translate("ui_settings", "Proxy IP:", 0));
        label_8->setText(QApplication::translate("ui_settings", "Proxy Port:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabNetwork), QApplication::translate("ui_settings", "Network", 0));
        btnOk->setText(QApplication::translate("ui_settings", "OK", 0));
        btnCancel->setText(QApplication::translate("ui_settings", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class ui_settings: public Ui_ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_SETTINGS_H
