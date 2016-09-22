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
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImport;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1044, 800);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 127);"));
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QStringLiteral("actionFile"));
        action3D_Image = new QAction(MainWindow);
        action3D_Image->setObjectName(QStringLiteral("action3D_Image"));
        actionLabel_map = new QAction(MainWindow);
        actionLabel_map->setObjectName(QStringLiteral("actionLabel_map"));
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
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1044, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuImport = new QMenu(menuFile);
        menuImport->setObjectName(QStringLiteral("menuImport"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(menuImport->menuAction());
        menuImport->addAction(action3D_Image);
        menuImport->addAction(actionLabel_map);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionFile->setText(QApplication::translate("MainWindow", "File", 0));
        action3D_Image->setText(QApplication::translate("MainWindow", "3D Image", 0));
        actionLabel_map->setText(QApplication::translate("MainWindow", "Label map", 0));
        labelFigureZ->setText(QString());
        labelFigureY->setText(QString());
        labelFigureX->setText(QString());
        rotateZ_90AntiClockwise->setText(QString());
        mirrorZ->setText(QString());
        rotateY_90Anticlockwise->setText(QString());
        rotateY_90Anticlockwise_2->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "BC", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
