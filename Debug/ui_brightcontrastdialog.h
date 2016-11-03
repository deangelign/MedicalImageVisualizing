/********************************************************************************
** Form generated from reading UI file 'brightcontrastdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BRIGHTCONTRASTDIALOG_H
#define UI_BRIGHTCONTRASTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BrightContrastDialog
{
public:
    QDialogButtonBox *buttonBox;
    QSlider *horizontalSliderBrightDIalog;
    QLabel *label;
    QLabel *label_2;
    QSlider *horizontalSliderContrastDialog;
    QCheckBox *checkBoxNormalizacao;
    QCheckBox *checkBoxNegativo;
    QSpinBox *spinBoxBright;
    QSpinBox *spinBoxContrast;
    QCheckBox *checkBoxLimiarizacao;
    QSpinBox *spinBoxLimiarizacao;
<<<<<<< HEAD
    QSlider *horizontalSlider;
=======
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58

    void setupUi(QDialog *BrightContrastDialog)
    {
        if (BrightContrastDialog->objectName().isEmpty())
            BrightContrastDialog->setObjectName(QStringLiteral("BrightContrastDialog"));
        BrightContrastDialog->resize(349, 240);
        buttonBox = new QDialogButtonBox(BrightContrastDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 200, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalSliderBrightDIalog = new QSlider(BrightContrastDialog);
        horizontalSliderBrightDIalog->setObjectName(QStringLiteral("horizontalSliderBrightDIalog"));
        horizontalSliderBrightDIalog->setGeometry(QRect(110, 30, 160, 16));
        horizontalSliderBrightDIalog->setMaximum(100);
        horizontalSliderBrightDIalog->setOrientation(Qt::Horizontal);
        label = new QLabel(BrightContrastDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 59, 14));
        label_2 = new QLabel(BrightContrastDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 59, 14));
        horizontalSliderContrastDialog = new QSlider(BrightContrastDialog);
        horizontalSliderContrastDialog->setObjectName(QStringLiteral("horizontalSliderContrastDialog"));
        horizontalSliderContrastDialog->setGeometry(QRect(110, 60, 160, 16));
        horizontalSliderContrastDialog->setMaximum(100);
        horizontalSliderContrastDialog->setOrientation(Qt::Horizontal);
        checkBoxNormalizacao = new QCheckBox(BrightContrastDialog);
        checkBoxNormalizacao->setObjectName(QStringLiteral("checkBoxNormalizacao"));
        checkBoxNormalizacao->setGeometry(QRect(10, 90, 111, 20));
        checkBoxNegativo = new QCheckBox(BrightContrastDialog);
        checkBoxNegativo->setObjectName(QStringLiteral("checkBoxNegativo"));
        checkBoxNegativo->setGeometry(QRect(10, 120, 111, 20));
        spinBoxBright = new QSpinBox(BrightContrastDialog);
        spinBoxBright->setObjectName(QStringLiteral("spinBoxBright"));
        spinBoxBright->setGeometry(QRect(280, 20, 47, 23));
        spinBoxBright->setMaximum(100);
        spinBoxContrast = new QSpinBox(BrightContrastDialog);
        spinBoxContrast->setObjectName(QStringLiteral("spinBoxContrast"));
        spinBoxContrast->setGeometry(QRect(280, 55, 47, 23));
        spinBoxContrast->setMaximum(100);
        checkBoxLimiarizacao = new QCheckBox(BrightContrastDialog);
        checkBoxLimiarizacao->setObjectName(QStringLiteral("checkBoxLimiarizacao"));
        checkBoxLimiarizacao->setGeometry(QRect(10, 150, 101, 20));
        spinBoxLimiarizacao = new QSpinBox(BrightContrastDialog);
        spinBoxLimiarizacao->setObjectName(QStringLiteral("spinBoxLimiarizacao"));
<<<<<<< HEAD
        spinBoxLimiarizacao->setGeometry(QRect(280, 145, 47, 23));
        spinBoxLimiarizacao->setMaximum(100);
        horizontalSlider = new QSlider(BrightContrastDialog);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 150, 160, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
=======
        spinBoxLimiarizacao->setGeometry(QRect(130, 145, 47, 23));
        spinBoxLimiarizacao->setMaximum(100);
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58

        retranslateUi(BrightContrastDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BrightContrastDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BrightContrastDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BrightContrastDialog);
    } // setupUi

    void retranslateUi(QDialog *BrightContrastDialog)
    {
        BrightContrastDialog->setWindowTitle(QApplication::translate("BrightContrastDialog", "Dialog", 0));
        label->setText(QApplication::translate("BrightContrastDialog", "Brilho", 0));
        label_2->setText(QApplication::translate("BrightContrastDialog", "Contrast", 0));
        checkBoxNormalizacao->setText(QApplication::translate("BrightContrastDialog", "Normaliza\303\247\303\243o", 0));
        checkBoxNegativo->setText(QApplication::translate("BrightContrastDialog", "Negativo", 0));
        checkBoxLimiarizacao->setText(QApplication::translate("BrightContrastDialog", "Limiariza\303\247\303\243o", 0));
    } // retranslateUi

};

namespace Ui {
    class BrightContrastDialog: public Ui_BrightContrastDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BRIGHTCONTRASTDIALOG_H
