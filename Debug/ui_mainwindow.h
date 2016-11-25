/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFile;
    QAction *action3D_Image;
    QAction *actionLabel_map;
    QAction *actionRefactor;
    QAction *actionGenerate_New_Volume;
    QWidget *centralWidget;
    QLabel *labelFigureZ;
    QLabel *labelFigureY;
    QLabel *labelFigureX;
    QSpinBox *spinBoxImageZ;
    QSpinBox *spinBoxImageY;
    QSpinBox *spinBoxImageX;
    QPushButton *rotateZ_90AntiClockwise;
    QPushButton *mirrorZ;
    QPushButton *rotateY_90Anticlockwise;
    QPushButton *rotateY_90Anticlockwise_2;
    QPushButton *pushButton;
    QLabel *labelFigureXYZ;
    QPushButton *pushButton_2;
    QDoubleSpinBox *SpinBoxPointX;
    QDoubleSpinBox *SpinBoxPointY;
    QDoubleSpinBox *SpinBoxPointZ;
    QDoubleSpinBox *SpinBoxVectorX;
    QDoubleSpinBox *SpinBoxVectorY;
    QDoubleSpinBox *SpinBoxVectorZ;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxThetaX;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBoxThetaY;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImport;
    QMenu *menuTools;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1161, 854);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 127);"));
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QStringLiteral("actionFile"));
        action3D_Image = new QAction(MainWindow);
        action3D_Image->setObjectName(QStringLiteral("action3D_Image"));
        actionLabel_map = new QAction(MainWindow);
        actionLabel_map->setObjectName(QStringLiteral("actionLabel_map"));
        actionRefactor = new QAction(MainWindow);
        actionRefactor->setObjectName(QStringLiteral("actionRefactor"));
        actionGenerate_New_Volume = new QAction(MainWindow);
        actionGenerate_New_Volume->setObjectName(QStringLiteral("actionGenerate_New_Volume"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelFigureZ = new QLabel(centralWidget);
        labelFigureZ->setObjectName(QStringLiteral("labelFigureZ"));
        labelFigureZ->setGeometry(QRect(32, 8, 400, 350));
        labelFigureZ->setContextMenuPolicy(Qt::CustomContextMenu);
        labelFigureZ->setAutoFillBackground(false);
        labelFigureZ->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        labelFigureZ->setWordWrap(false);
        labelFigureY = new QLabel(centralWidget);
        labelFigureY->setObjectName(QStringLiteral("labelFigureY"));
        labelFigureY->setGeometry(QRect(580, 8, 400, 350));
        labelFigureY->setBaseSize(QSize(0, 0));
        labelFigureY->setContextMenuPolicy(Qt::CustomContextMenu);
        labelFigureY->setAutoFillBackground(false);
        labelFigureY->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        labelFigureY->setWordWrap(false);
        labelFigureX = new QLabel(centralWidget);
        labelFigureX->setObjectName(QStringLiteral("labelFigureX"));
        labelFigureX->setGeometry(QRect(32, 372, 400, 350));
        labelFigureX->setContextMenuPolicy(Qt::CustomContextMenu);
        labelFigureX->setAutoFillBackground(false);
        labelFigureX->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        labelFigureX->setWordWrap(false);
        spinBoxImageZ = new QSpinBox(centralWidget);
        spinBoxImageZ->setObjectName(QStringLiteral("spinBoxImageZ"));
        spinBoxImageZ->setGeometry(QRect(440, 8, 47, 23));
        spinBoxImageZ->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        spinBoxImageY = new QSpinBox(centralWidget);
        spinBoxImageY->setObjectName(QStringLiteral("spinBoxImageY"));
        spinBoxImageY->setGeometry(QRect(990, 8, 47, 23));
        spinBoxImageY->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        spinBoxImageX = new QSpinBox(centralWidget);
        spinBoxImageX->setObjectName(QStringLiteral("spinBoxImageX"));
        spinBoxImageX->setGeometry(QRect(440, 372, 47, 23));
        spinBoxImageX->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        rotateZ_90AntiClockwise = new QPushButton(centralWidget);
        rotateZ_90AntiClockwise->setObjectName(QStringLiteral("rotateZ_90AntiClockwise"));
        rotateZ_90AntiClockwise->setGeometry(QRect(440, 32, 30, 30));
        rotateZ_90AntiClockwise->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QStringLiteral("../icons/rotationAntiCloskwise.png"), QSize(), QIcon::Normal, QIcon::Off);
        rotateZ_90AntiClockwise->setIcon(icon);
        rotateZ_90AntiClockwise->setIconSize(QSize(20, 20));
        mirrorZ = new QPushButton(centralWidget);
        mirrorZ->setObjectName(QStringLiteral("mirrorZ"));
        mirrorZ->setGeometry(QRect(440, 64, 30, 30));
        mirrorZ->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../icons/plainicon.com-40295-256px.png"), QSize(), QIcon::Normal, QIcon::Off);
        mirrorZ->setIcon(icon1);
        mirrorZ->setIconSize(QSize(20, 20));
        rotateY_90Anticlockwise = new QPushButton(centralWidget);
        rotateY_90Anticlockwise->setObjectName(QStringLiteral("rotateY_90Anticlockwise"));
        rotateY_90Anticlockwise->setGeometry(QRect(990, 32, 30, 30));
        rotateY_90Anticlockwise->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        rotateY_90Anticlockwise->setIcon(icon);
        rotateY_90Anticlockwise->setIconSize(QSize(20, 20));
        rotateY_90Anticlockwise_2 = new QPushButton(centralWidget);
        rotateY_90Anticlockwise_2->setObjectName(QStringLiteral("rotateY_90Anticlockwise_2"));
        rotateY_90Anticlockwise_2->setGeometry(QRect(440, 396, 30, 30));
        rotateY_90Anticlockwise_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        rotateY_90Anticlockwise_2->setIcon(icon);
        rotateY_90Anticlockwise_2->setIconSize(QSize(20, 20));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(440, 100, 30, 30));
        labelFigureXYZ = new QLabel(centralWidget);
        labelFigureXYZ->setObjectName(QStringLiteral("labelFigureXYZ"));
        labelFigureXYZ->setGeometry(QRect(580, 372, 400, 350));
        labelFigureXYZ->setContextMenuPolicy(Qt::CustomContextMenu);
        labelFigureXYZ->setAutoFillBackground(false);
        labelFigureXYZ->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        labelFigureXYZ->setWordWrap(false);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(990, 380, 80, 22));
        SpinBoxPointX = new QDoubleSpinBox(centralWidget);
        SpinBoxPointX->setObjectName(QStringLiteral("SpinBoxPointX"));
        SpinBoxPointX->setGeometry(QRect(990, 460, 66, 23));
        SpinBoxPointX->setMinimum(-9999);
        SpinBoxPointX->setMaximum(9999);
        SpinBoxPointY = new QDoubleSpinBox(centralWidget);
        SpinBoxPointY->setObjectName(QStringLiteral("SpinBoxPointY"));
        SpinBoxPointY->setGeometry(QRect(990, 490, 66, 23));
        SpinBoxPointY->setMinimum(-9999);
        SpinBoxPointY->setMaximum(9999);
        SpinBoxPointZ = new QDoubleSpinBox(centralWidget);
        SpinBoxPointZ->setObjectName(QStringLiteral("SpinBoxPointZ"));
        SpinBoxPointZ->setGeometry(QRect(990, 520, 66, 23));
        SpinBoxPointZ->setMinimum(-9999);
        SpinBoxPointZ->setMaximum(9999);
        SpinBoxVectorX = new QDoubleSpinBox(centralWidget);
        SpinBoxVectorX->setObjectName(QStringLiteral("SpinBoxVectorX"));
        SpinBoxVectorX->setGeometry(QRect(1070, 460, 66, 23));
        SpinBoxVectorX->setMinimum(-9999);
        SpinBoxVectorX->setMaximum(9999);
        SpinBoxVectorX->setSingleStep(0.1);
        SpinBoxVectorY = new QDoubleSpinBox(centralWidget);
        SpinBoxVectorY->setObjectName(QStringLiteral("SpinBoxVectorY"));
        SpinBoxVectorY->setGeometry(QRect(1070, 490, 66, 23));
        SpinBoxVectorY->setMinimum(-9999);
        SpinBoxVectorY->setMaximum(9999);
        SpinBoxVectorY->setSingleStep(0.1);
        SpinBoxVectorZ = new QDoubleSpinBox(centralWidget);
        SpinBoxVectorZ->setObjectName(QStringLiteral("SpinBoxVectorZ"));
        SpinBoxVectorZ->setGeometry(QRect(1070, 520, 66, 23));
        SpinBoxVectorZ->setMinimum(-9999);
        SpinBoxVectorZ->setMaximum(9999);
        SpinBoxVectorZ->setSingleStep(0.1);
        SpinBoxVectorZ->setValue(1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1000, 440, 16, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1080, 430, 16, 16));
        doubleSpinBoxThetaX = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxThetaX->setObjectName(QStringLiteral("doubleSpinBoxThetaX"));
        doubleSpinBoxThetaX->setGeometry(QRect(990, 600, 66, 23));
        doubleSpinBoxThetaX->setDecimals(3);
        doubleSpinBoxThetaX->setMinimum(-360);
        doubleSpinBoxThetaX->setMaximum(360);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1000, 580, 51, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1070, 580, 59, 14));
        doubleSpinBoxThetaY = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxThetaY->setObjectName(QStringLiteral("doubleSpinBoxThetaY"));
        doubleSpinBoxThetaY->setGeometry(QRect(1070, 600, 66, 23));
        doubleSpinBoxThetaY->setDecimals(3);
        doubleSpinBoxThetaY->setMinimum(-360);
        doubleSpinBoxThetaY->setMaximum(360);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1161, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuImport = new QMenu(menuFile);
        menuImport->setObjectName(QStringLiteral("menuImport"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addAction(menuImport->menuAction());
        menuImport->addAction(action3D_Image);
        menuImport->addAction(actionLabel_map);
        menuTools->addAction(actionRefactor);
        menuTools->addAction(actionGenerate_New_Volume);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionFile->setText(QApplication::translate("MainWindow", "File", 0));
        action3D_Image->setText(QApplication::translate("MainWindow", "3D Image", 0));
        actionLabel_map->setText(QApplication::translate("MainWindow", "Label map", 0));
        actionRefactor->setText(QApplication::translate("MainWindow", "Refactor", 0));
        actionGenerate_New_Volume->setText(QApplication::translate("MainWindow", "Generate New Volume", 0));
        labelFigureZ->setText(QString());
        labelFigureY->setText(QString());
        labelFigureX->setText(QString());
        rotateZ_90AntiClockwise->setText(QString());
        mirrorZ->setText(QString());
        rotateY_90Anticlockwise->setText(QString());
        rotateY_90Anticlockwise_2->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "BC", 0));
        labelFigureXYZ->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", 0));
        label->setText(QApplication::translate("MainWindow", "P", 0));
        label_2->setText(QApplication::translate("MainWindow", "V", 0));
        label_3->setText(QApplication::translate("MainWindow", "ThetaX", 0));
        label_4->setText(QApplication::translate("MainWindow", "Theta Y", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
