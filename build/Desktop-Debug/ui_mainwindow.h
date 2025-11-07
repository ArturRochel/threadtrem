/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_trilho_top;
    QLabel *label_trilho_mid;
    QLabel *label_trilho_bot;
    QLabel *label_trilho_left;
    QLabel *label_trilho_right;
    QLabel *label_trilho_top_L;
    QLabel *label_trilho_top_R;
    QLabel *label_trilho_bot_M;
    QLabel *label_trem1;
    QLabel *label_trem2;
    QLabel *label_trem3;
    QLabel *label_trem4;
    QLabel *label_trem5;
    QLabel *label_trem6;
    QSlider *sliderTrem1;
    QSlider *sliderTrem2;
    QSlider *sliderTrem3;
    QSlider *sliderTrem4;
    QSlider *sliderTrem5;
    QSlider *sliderTrem6;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(929, 760);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        label_trilho_top = new QLabel(centralWidget);
        label_trilho_top->setObjectName("label_trilho_top");
        label_trilho_top->setGeometry(QRect(100, 100, 642, 34));
        label_trilho_top->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho_mid = new QLabel(centralWidget);
        label_trilho_mid->setObjectName("label_trilho_mid");
        label_trilho_mid->setGeometry(QRect(100, 300, 642, 34));
        label_trilho_mid->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho_bot = new QLabel(centralWidget);
        label_trilho_bot->setObjectName("label_trilho_bot");
        label_trilho_bot->setGeometry(QRect(100, 500, 642, 34));
        label_trilho_bot->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho_left = new QLabel(centralWidget);
        label_trilho_left->setObjectName("label_trilho_left");
        label_trilho_left->setGeometry(QRect(100, 100, 42, 434));
        label_trilho_left->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho_right = new QLabel(centralWidget);
        label_trilho_right->setObjectName("label_trilho_right");
        label_trilho_right->setGeometry(QRect(700, 100, 42, 434));
        label_trilho_right->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho_top_L = new QLabel(centralWidget);
        label_trilho_top_L->setObjectName("label_trilho_top_L");
        label_trilho_top_L->setGeometry(QRect(300, 100, 42, 234));
        label_trilho_top_L->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho_top_R = new QLabel(centralWidget);
        label_trilho_top_R->setObjectName("label_trilho_top_R");
        label_trilho_top_R->setGeometry(QRect(500, 100, 42, 234));
        label_trilho_top_R->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trilho_bot_M = new QLabel(centralWidget);
        label_trilho_bot_M->setObjectName("label_trilho_bot_M");
        label_trilho_bot_M->setGeometry(QRect(400, 300, 42, 234));
        label_trilho_bot_M->setStyleSheet(QString::fromUtf8("QLabel { background: yellow}"));
        label_trem1 = new QLabel(centralWidget);
        label_trem1->setObjectName("label_trem1");
        label_trem1->setGeometry(QRect(100, 300, 42, 34));
        label_trem1->setStyleSheet(QString::fromUtf8("QLabel { background: #5BC724;\n"
" color: black}"));
        label_trem2 = new QLabel(centralWidget);
        label_trem2->setObjectName("label_trem2");
        label_trem2->setGeometry(QRect(200, 500, 42, 34));
        label_trem2->setStyleSheet(QString::fromUtf8("QLabel { background: #F0820A;\n"
" color: black}"));
        label_trem3 = new QLabel(centralWidget);
        label_trem3->setObjectName("label_trem3");
        label_trem3->setGeometry(QRect(400, 300, 42, 34));
        label_trem3->setStyleSheet(QString::fromUtf8("QLabel { background: #8B27F5;\n"
" color: black}"));
        label_trem4 = new QLabel(centralWidget);
        label_trem4->setObjectName("label_trem4");
        label_trem4->setGeometry(QRect(500, 100, 42, 34));
        label_trem4->setStyleSheet(QString::fromUtf8("QLabel { background: #2779F5;\n"
" color: black}"));
        label_trem5 = new QLabel(centralWidget);
        label_trem5->setObjectName("label_trem5");
        label_trem5->setGeometry(QRect(300, 100, 42, 34));
        label_trem5->setStyleSheet(QString::fromUtf8("QLabel { background: #D60606;\n"
" color: black}"));
        label_trem6 = new QLabel(centralWidget);
        label_trem6->setObjectName("label_trem6");
        label_trem6->setGeometry(QRect(300, 500, 42, 34));
        label_trem6->setStyleSheet(QString::fromUtf8("QLabel { background: black;\n"
" color: white}"));
        sliderTrem1 = new QSlider(centralWidget);
        sliderTrem1->setObjectName("sliderTrem1");
        sliderTrem1->setGeometry(QRect(790, 230, 100, 22));
        sliderTrem1->setStyleSheet(QString::fromUtf8(""));
        sliderTrem1->setMinimum(0);
        sliderTrem1->setMaximum(200);
        sliderTrem1->setValue(50);
        sliderTrem1->setOrientation(Qt::Orientation::Horizontal);
        sliderTrem2 = new QSlider(centralWidget);
        sliderTrem2->setObjectName("sliderTrem2");
        sliderTrem2->setGeometry(QRect(790, 260, 100, 22));
        sliderTrem2->setMinimum(0);
        sliderTrem2->setMaximum(200);
        sliderTrem2->setValue(50);
        sliderTrem2->setOrientation(Qt::Orientation::Horizontal);
        sliderTrem3 = new QSlider(centralWidget);
        sliderTrem3->setObjectName("sliderTrem3");
        sliderTrem3->setGeometry(QRect(790, 290, 100, 22));
        sliderTrem3->setMinimum(0);
        sliderTrem3->setMaximum(200);
        sliderTrem3->setValue(50);
        sliderTrem3->setOrientation(Qt::Orientation::Horizontal);
        sliderTrem4 = new QSlider(centralWidget);
        sliderTrem4->setObjectName("sliderTrem4");
        sliderTrem4->setGeometry(QRect(790, 320, 100, 22));
        sliderTrem4->setMinimum(0);
        sliderTrem4->setMaximum(200);
        sliderTrem4->setValue(50);
        sliderTrem4->setOrientation(Qt::Orientation::Horizontal);
        sliderTrem5 = new QSlider(centralWidget);
        sliderTrem5->setObjectName("sliderTrem5");
        sliderTrem5->setGeometry(QRect(790, 350, 100, 22));
        sliderTrem5->setMinimum(0);
        sliderTrem5->setMaximum(200);
        sliderTrem5->setValue(50);
        sliderTrem5->setOrientation(Qt::Orientation::Horizontal);
        sliderTrem6 = new QSlider(centralWidget);
        sliderTrem6->setObjectName("sliderTrem6");
        sliderTrem6->setGeometry(QRect(790, 380, 100, 22));
        sliderTrem6->setMinimum(0);
        sliderTrem6->setMaximum(200);
        sliderTrem6->setValue(50);
        sliderTrem6->setOrientation(Qt::Orientation::Horizontal);
        MainWindow->setCentralWidget(centralWidget);
        sliderTrem1->raise();
        sliderTrem2->raise();
        sliderTrem3->raise();
        sliderTrem4->raise();
        sliderTrem5->raise();
        sliderTrem6->raise();
        label_trilho_top->raise();
        label_trilho_mid->raise();
        label_trilho_bot->raise();
        label_trilho_left->raise();
        label_trilho_right->raise();
        label_trilho_top_L->raise();
        label_trilho_top_R->raise();
        label_trilho_bot_M->raise();
        label_trem1->raise();
        label_trem2->raise();
        label_trem3->raise();
        label_trem4->raise();
        label_trem5->raise();
        label_trem6->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 929, 24));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Simulador de Trens", nullptr));
        label_trilho_top->setText(QString());
        label_trilho_mid->setText(QString());
        label_trilho_bot->setText(QString());
        label_trilho_left->setText(QString());
        label_trilho_right->setText(QString());
        label_trilho_top_L->setText(QString());
        label_trilho_top_R->setText(QString());
        label_trilho_bot_M->setText(QString());
        label_trem1->setText(QCoreApplication::translate("MainWindow", "T1", nullptr));
        label_trem2->setText(QCoreApplication::translate("MainWindow", "T2", nullptr));
        label_trem3->setText(QCoreApplication::translate("MainWindow", "T3", nullptr));
        label_trem4->setText(QCoreApplication::translate("MainWindow", "T4", nullptr));
        label_trem5->setText(QCoreApplication::translate("MainWindow", "T5", nullptr));
        label_trem6->setText(QCoreApplication::translate("MainWindow", "T6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
