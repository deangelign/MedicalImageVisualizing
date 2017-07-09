/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *labelNumberObjets;
    QLabel *drawFrameLabel;
    QLabel *thetaXLabel;
    QDoubleSpinBox *doubleSpinBoxThetaX;
    QLabel *thetaYLabel;
    QDoubleSpinBox *doubleSpinBoxThetaY;
    QLabel *alphaSLabel;
    QLineEdit *lineEditAlphasValues;
    QLabel *phongLabel;
    QLineEdit *lineEditPhongValues;
    QCheckBox *checkBox;
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
        MainWindow->resize(1176, 854);
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
        pushButton_2->setEnabled(true);
        pushButton_2->setGeometry(QRect(990, 380, 80, 22));
        SpinBoxPointX = new QDoubleSpinBox(centralWidget);
        SpinBoxPointX->setObjectName(QStringLiteral("SpinBoxPointX"));
        SpinBoxPointX->setGeometry(QRect(990, 430, 66, 23));
        SpinBoxPointX->setMinimum(-9999);
        SpinBoxPointX->setMaximum(9999);
        SpinBoxPointY = new QDoubleSpinBox(centralWidget);
        SpinBoxPointY->setObjectName(QStringLiteral("SpinBoxPointY"));
        SpinBoxPointY->setGeometry(QRect(990, 460, 66, 23));
        SpinBoxPointY->setMinimum(-9999);
        SpinBoxPointY->setMaximum(9999);
        SpinBoxPointZ = new QDoubleSpinBox(centralWidget);
        SpinBoxPointZ->setObjectName(QStringLiteral("SpinBoxPointZ"));
        SpinBoxPointZ->setGeometry(QRect(990, 490, 66, 23));
        SpinBoxPointZ->setMinimum(-9999);
        SpinBoxPointZ->setMaximum(9999);
        SpinBoxVectorX = new QDoubleSpinBox(centralWidget);
        SpinBoxVectorX->setObjectName(QStringLiteral("SpinBoxVectorX"));
        SpinBoxVectorX->setGeometry(QRect(1070, 430, 66, 23));
        SpinBoxVectorX->setMinimum(-9999);
        SpinBoxVectorX->setMaximum(9999);
        SpinBoxVectorX->setSingleStep(0.1);
        SpinBoxVectorY = new QDoubleSpinBox(centralWidget);
        SpinBoxVectorY->setObjectName(QStringLiteral("SpinBoxVectorY"));
        SpinBoxVectorY->setGeometry(QRect(1070, 460, 66, 23));
        SpinBoxVectorY->setMinimum(-9999);
        SpinBoxVectorY->setMaximum(9999);
        SpinBoxVectorY->setSingleStep(0.1);
        SpinBoxVectorZ = new QDoubleSpinBox(centralWidget);
        SpinBoxVectorZ->setObjectName(QStringLiteral("SpinBoxVectorZ"));
        SpinBoxVectorZ->setGeometry(QRect(1070, 490, 66, 23));
        SpinBoxVectorZ->setMinimum(-9999);
        SpinBoxVectorZ->setMaximum(9999);
        SpinBoxVectorZ->setSingleStep(0.1);
        SpinBoxVectorZ->setValue(1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1000, 410, 16, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1080, 410, 16, 16));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(990, 520, 188, 166));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        labelNumberObjets = new QLabel(formLayoutWidget);
        labelNumberObjets->setObjectName(QStringLiteral("labelNumberObjets"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelNumberObjets);

        drawFrameLabel = new QLabel(formLayoutWidget);
        drawFrameLabel->setObjectName(QStringLiteral("drawFrameLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, drawFrameLabel);

        thetaXLabel = new QLabel(formLayoutWidget);
        thetaXLabel->setObjectName(QStringLiteral("thetaXLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, thetaXLabel);

        doubleSpinBoxThetaX = new QDoubleSpinBox(formLayoutWidget);
        doubleSpinBoxThetaX->setObjectName(QStringLiteral("doubleSpinBoxThetaX"));
        doubleSpinBoxThetaX->setMinimum(-360);
        doubleSpinBoxThetaX->setMaximum(360000);
        doubleSpinBoxThetaX->setSingleStep(1);

        formLayout->setWidget(2, QFormLayout::FieldRole, doubleSpinBoxThetaX);

        thetaYLabel = new QLabel(formLayoutWidget);
        thetaYLabel->setObjectName(QStringLiteral("thetaYLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, thetaYLabel);

        doubleSpinBoxThetaY = new QDoubleSpinBox(formLayoutWidget);
        doubleSpinBoxThetaY->setObjectName(QStringLiteral("doubleSpinBoxThetaY"));
        doubleSpinBoxThetaY->setMinimum(-360);
        doubleSpinBoxThetaY->setMaximum(360);
        doubleSpinBoxThetaY->setSingleStep(1);

        formLayout->setWidget(3, QFormLayout::FieldRole, doubleSpinBoxThetaY);

        alphaSLabel = new QLabel(formLayoutWidget);
        alphaSLabel->setObjectName(QStringLiteral("alphaSLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, alphaSLabel);

        lineEditAlphasValues = new QLineEdit(formLayoutWidget);
        lineEditAlphasValues->setObjectName(QStringLiteral("lineEditAlphasValues"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditAlphasValues);

        phongLabel = new QLabel(formLayoutWidget);
        phongLabel->setObjectName(QStringLiteral("phongLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, phongLabel);

        lineEditPhongValues = new QLineEdit(formLayoutWidget);
        lineEditPhongValues->setObjectName(QStringLiteral("lineEditPhongValues"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditPhongValues);

        checkBox = new QCheckBox(formLayoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, checkBox);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1176, 22));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionFile->setText(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        action3D_Image->setText(QApplication::translate("MainWindow", "3D Image", Q_NULLPTR));
        actionLabel_map->setText(QApplication::translate("MainWindow", "Label map", Q_NULLPTR));
        actionRefactor->setText(QApplication::translate("MainWindow", "Refactor", Q_NULLPTR));
        actionGenerate_New_Volume->setText(QApplication::translate("MainWindow", "Generate New Volume", Q_NULLPTR));
        labelFigureZ->setText(QString());
        labelFigureY->setText(QString());
        labelFigureX->setText(QString());
        rotateZ_90AntiClockwise->setText(QString());
        mirrorZ->setText(QString());
        rotateY_90Anticlockwise->setText(QString());
        rotateY_90Anticlockwise_2->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "BC", Q_NULLPTR));
        labelFigureXYZ->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "debug", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "P", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "V", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "# objects: ", Q_NULLPTR));
        labelNumberObjets->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        drawFrameLabel->setText(QApplication::translate("MainWindow", "drawFrame:", Q_NULLPTR));
        thetaXLabel->setText(QApplication::translate("MainWindow", "thetaX:", Q_NULLPTR));
        thetaYLabel->setText(QApplication::translate("MainWindow", "thetaY:", Q_NULLPTR));
        alphaSLabel->setText(QApplication::translate("MainWindow", "alpha(s):", Q_NULLPTR));
        phongLabel->setText(QApplication::translate("MainWindow", "phong:", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuImport->setTitle(QApplication::translate("MainWindow", "Import", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
