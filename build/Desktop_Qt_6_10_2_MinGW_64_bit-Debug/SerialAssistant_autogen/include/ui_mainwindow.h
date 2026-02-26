/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_main;
    QGroupBox *groupPort;
    QVBoxLayout *vlayout_port;
    QLabel *label;
    QHBoxLayout *hboxLayout;
    QComboBox *comboPort;
    QPushButton *btnRefresh;
    QLabel *label1;
    QComboBox *comboBaud;
    QLabel *label2;
    QComboBox *comboData;
    QLabel *label3;
    QComboBox *comboParity;
    QLabel *label4;
    QComboBox *comboStop;
    QFrame *frame;
    QPushButton *btnOpenClose;
    QFrame *frame1;
    QGroupBox *groupRecvOpt;
    QVBoxLayout *vboxLayout;
    QCheckBox *chkHexRecv;
    QCheckBox *chkTimestamp;
    QCheckBox *chkAutoScroll;
    QGroupBox *groupSendOpt;
    QVBoxLayout *vboxLayout1;
    QCheckBox *chkHexSend;
    QCheckBox *chkNewline;
    QGroupBox *groupTimedSend;
    QVBoxLayout *vboxLayout2;
    QCheckBox *chkTimedSend;
    QHBoxLayout *hboxLayout1;
    QLabel *label5;
    QSpinBox *spinInterval;
    QSpacerItem *spacerItem;
    QVBoxLayout *vlayout_right;
    QGroupBox *groupRecv;
    QVBoxLayout *vboxLayout3;
    QPlainTextEdit *textRecv;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem1;
    QPushButton *btnSave;
    QPushButton *btnClear;
    QGroupBox *groupSend;
    QVBoxLayout *vboxLayout4;
    QHBoxLayout *hboxLayout3;
    QLineEdit *editSend;
    QPushButton *btnSend;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_main = new QHBoxLayout(centralwidget);
        horizontalLayout_main->setSpacing(8);
        horizontalLayout_main->setObjectName("horizontalLayout_main");
        horizontalLayout_main->setContentsMargins(8, 8, 8, 8);
        groupPort = new QGroupBox(centralwidget);
        groupPort->setObjectName("groupPort");
        groupPort->setMaximumWidth(200);
        vlayout_port = new QVBoxLayout(groupPort);
        vlayout_port->setSpacing(6);
        vlayout_port->setObjectName("vlayout_port");
        label = new QLabel(groupPort);
        label->setObjectName("label");

        vlayout_port->addWidget(label);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        comboPort = new QComboBox(groupPort);
        comboPort->setObjectName("comboPort");
        comboPort->setMinimumWidth(120);

        hboxLayout->addWidget(comboPort);

        btnRefresh = new QPushButton(groupPort);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setMaximumWidth(45);

        hboxLayout->addWidget(btnRefresh);


        vlayout_port->addLayout(hboxLayout);

        label1 = new QLabel(groupPort);
        label1->setObjectName("label1");

        vlayout_port->addWidget(label1);

        comboBaud = new QComboBox(groupPort);
        comboBaud->setObjectName("comboBaud");

        vlayout_port->addWidget(comboBaud);

        label2 = new QLabel(groupPort);
        label2->setObjectName("label2");

        vlayout_port->addWidget(label2);

        comboData = new QComboBox(groupPort);
        comboData->setObjectName("comboData");

        vlayout_port->addWidget(comboData);

        label3 = new QLabel(groupPort);
        label3->setObjectName("label3");

        vlayout_port->addWidget(label3);

        comboParity = new QComboBox(groupPort);
        comboParity->setObjectName("comboParity");

        vlayout_port->addWidget(comboParity);

        label4 = new QLabel(groupPort);
        label4->setObjectName("label4");

        vlayout_port->addWidget(label4);

        comboStop = new QComboBox(groupPort);
        comboStop->setObjectName("comboStop");

        vlayout_port->addWidget(comboStop);

        frame = new QFrame(groupPort);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        vlayout_port->addWidget(frame);

        btnOpenClose = new QPushButton(groupPort);
        btnOpenClose->setObjectName("btnOpenClose");
        btnOpenClose->setMinimumHeight(36);

        vlayout_port->addWidget(btnOpenClose);

        frame1 = new QFrame(groupPort);
        frame1->setObjectName("frame1");
        frame1->setFrameShape(QFrame::HLine);
        frame1->setFrameShadow(QFrame::Sunken);

        vlayout_port->addWidget(frame1);

        groupRecvOpt = new QGroupBox(groupPort);
        groupRecvOpt->setObjectName("groupRecvOpt");
        vboxLayout = new QVBoxLayout(groupRecvOpt);
        vboxLayout->setObjectName("vboxLayout");
        chkHexRecv = new QCheckBox(groupRecvOpt);
        chkHexRecv->setObjectName("chkHexRecv");

        vboxLayout->addWidget(chkHexRecv);

        chkTimestamp = new QCheckBox(groupRecvOpt);
        chkTimestamp->setObjectName("chkTimestamp");

        vboxLayout->addWidget(chkTimestamp);

        chkAutoScroll = new QCheckBox(groupRecvOpt);
        chkAutoScroll->setObjectName("chkAutoScroll");
        chkAutoScroll->setChecked(true);

        vboxLayout->addWidget(chkAutoScroll);


        vlayout_port->addWidget(groupRecvOpt);

        groupSendOpt = new QGroupBox(groupPort);
        groupSendOpt->setObjectName("groupSendOpt");
        vboxLayout1 = new QVBoxLayout(groupSendOpt);
        vboxLayout1->setObjectName("vboxLayout1");
        chkHexSend = new QCheckBox(groupSendOpt);
        chkHexSend->setObjectName("chkHexSend");

        vboxLayout1->addWidget(chkHexSend);

        chkNewline = new QCheckBox(groupSendOpt);
        chkNewline->setObjectName("chkNewline");
        chkNewline->setChecked(true);

        vboxLayout1->addWidget(chkNewline);


        vlayout_port->addWidget(groupSendOpt);

        groupTimedSend = new QGroupBox(groupPort);
        groupTimedSend->setObjectName("groupTimedSend");
        vboxLayout2 = new QVBoxLayout(groupTimedSend);
        vboxLayout2->setObjectName("vboxLayout2");
        chkTimedSend = new QCheckBox(groupTimedSend);
        chkTimedSend->setObjectName("chkTimedSend");

        vboxLayout2->addWidget(chkTimedSend);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        label5 = new QLabel(groupTimedSend);
        label5->setObjectName("label5");

        hboxLayout1->addWidget(label5);

        spinInterval = new QSpinBox(groupTimedSend);
        spinInterval->setObjectName("spinInterval");
        spinInterval->setMinimum(10);
        spinInterval->setMaximum(60000);
        spinInterval->setValue(1000);

        hboxLayout1->addWidget(spinInterval);


        vboxLayout2->addLayout(hboxLayout1);


        vlayout_port->addWidget(groupTimedSend);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vlayout_port->addItem(spacerItem);


        horizontalLayout_main->addWidget(groupPort);

        vlayout_right = new QVBoxLayout();
        vlayout_right->setSpacing(6);
        vlayout_right->setObjectName("vlayout_right");
        groupRecv = new QGroupBox(centralwidget);
        groupRecv->setObjectName("groupRecv");
        vboxLayout3 = new QVBoxLayout(groupRecv);
        vboxLayout3->setObjectName("vboxLayout3");
        textRecv = new QPlainTextEdit(groupRecv);
        textRecv->setObjectName("textRecv");
        textRecv->setReadOnly(true);

        vboxLayout3->addWidget(textRecv);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem1);

        btnSave = new QPushButton(groupRecv);
        btnSave->setObjectName("btnSave");

        hboxLayout2->addWidget(btnSave);

        btnClear = new QPushButton(groupRecv);
        btnClear->setObjectName("btnClear");

        hboxLayout2->addWidget(btnClear);


        vboxLayout3->addLayout(hboxLayout2);


        vlayout_right->addWidget(groupRecv);

        groupSend = new QGroupBox(centralwidget);
        groupSend->setObjectName("groupSend");
        groupSend->setMaximumHeight(100);
        vboxLayout4 = new QVBoxLayout(groupSend);
        vboxLayout4->setObjectName("vboxLayout4");
        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName("hboxLayout3");
        editSend = new QLineEdit(groupSend);
        editSend->setObjectName("editSend");

        hboxLayout3->addWidget(editSend);

        btnSend = new QPushButton(groupSend);
        btnSend->setObjectName("btnSend");
        btnSend->setMinimumWidth(80);
        btnSend->setMinimumHeight(32);

        hboxLayout3->addWidget(btnSend);


        vboxLayout4->addLayout(hboxLayout3);


        vlayout_right->addWidget(groupSend);


        horizontalLayout_main->addLayout(vlayout_right);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\212\251\346\211\213", nullptr));
        groupPort->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\351\205\215\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        btnOpenClose->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnOpenClose->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #4CAF50; color: white; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #45a049; }\n"
"QPushButton:pressed { background-color: #3d8b40; }", nullptr));
        groupRecvOpt->setTitle(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\351\200\211\351\241\271", nullptr));
        chkHexRecv->setText(QCoreApplication::translate("MainWindow", "HEX \346\230\276\347\244\272", nullptr));
        chkTimestamp->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\227\266\351\227\264\346\210\263", nullptr));
        chkAutoScroll->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\346\273\232\345\212\250", nullptr));
        groupSendOpt->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\351\200\211\351\241\271", nullptr));
        chkHexSend->setText(QCoreApplication::translate("MainWindow", "HEX \345\217\221\351\200\201", nullptr));
        chkNewline->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214(CR+LF)", nullptr));
        groupTimedSend->setTitle(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        chkTimedSend->setText(QCoreApplication::translate("MainWindow", "\345\220\257\347\224\250\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "\351\227\264\351\232\224(ms)", nullptr));
        groupRecv->setTitle(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\345\214\272", nullptr));
        textRecv->setStyleSheet(QCoreApplication::translate("MainWindow", "QPlainTextEdit { font-family: Consolas, Monaco, monospace; font-size: 12px; background-color: #1e1e1e; color: #d4d4d4; }", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\216\245\346\224\266", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        groupSend->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\214\272", nullptr));
        editSend->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\217\221\351\200\201\345\206\205\345\256\271\357\274\214\345\233\236\350\275\246\346\210\226\347\202\271\345\207\273\345\217\221\351\200\201...", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221 \351\200\201", nullptr));
        btnSend->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #2196F3; color: white; border-radius: 4px; font-weight: bold; }\n"
"QPushButton:hover { background-color: #1976D2; }\n"
"QPushButton:pressed { background-color: #1565C0; }", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
