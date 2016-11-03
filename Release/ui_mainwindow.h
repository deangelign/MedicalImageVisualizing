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
        labelFigureZ->setGeometry(QRect(32, 16, 400, 350));
        labelFigureZ->setAutoFillBackground(false);
        labelFigureZ->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        labelFigureZ->setWordWrap(false);
        labelFigureY = new QLabel(centralWidget);
        labelFigureY->setObjectName(QStringLiteral("labelFigureY"));
        labelFigureY->setGeometry(QRect(580, 16, 400, 350));
        labelFigureY->setAutoFillBackground(false);
        labelFigureY->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        labelFigureY->setWordWrap(false);
        labelFigureX = new QLabel(centralWidget);
        labelFigureX->setObjectName(QStringLiteral("labelFigureX"));
        labelFigureX->setGeometry(QRect(32, 400, 400, 350));
        labelFigureX->setAutoFillBackground(false);
        labelFigureX->setStyleSheet(QLatin1String("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"background-color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        labelFigureX->setWordWrap(false);
        spinBoxImageZ = new QSpinBox(centralWidget);
        spinBoxImageZ->setObjectName(QStringLiteral("spinBoxImageZ"));
        spinBoxImageZ->setGeometry(QRect(442, 16, 47, 23));
        spinBoxImageZ->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        spinBoxImageY = new QSpinBox(centralWidget);
        spinBoxImageY->setObjectName(QStringLiteral("spinBoxImageY"));
        spinBoxImageY->setGeometry(QRect(990, 16, 47, 23));
        spinBoxImageY->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        spinBoxImageX = new QSpinBox(centralWidget);
        spinBoxImageX->setObjectName(QStringLiteral("spinBoxImageX"));
        spinBoxImageX->setGeometry(QRect(442, 400, 47, 23));
        spinBoxImageX->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
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
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
