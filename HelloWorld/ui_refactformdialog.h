/********************************************************************************
** Form generated from reading UI file 'refactformdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REFACTFORMDIALOG_H
#define UI_REFACTFORMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_RefactFormDialog
{
public:
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *spinBoxRefactDx;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *spinBoxRefactDy;
    QDoubleSpinBox *spinBoxRefactDz;

    void setupUi(QDialog *RefactFormDialog)
    {
        if (RefactFormDialog->objectName().isEmpty())
            RefactFormDialog->setObjectName(QStringLiteral("RefactFormDialog"));
        RefactFormDialog->resize(385, 124);
        RefactFormDialog->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 127);"));
        buttonBox = new QDialogButtonBox(RefactFormDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(70, 80, 301, 32));
        buttonBox->setStyleSheet(QStringLiteral("background-color: rgb(170, 170, 127);"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        spinBoxRefactDx = new QDoubleSpinBox(RefactFormDialog);
        spinBoxRefactDx->setObjectName(QStringLiteral("spinBoxRefactDx"));
        spinBoxRefactDx->setGeometry(QRect(40, 40, 71, 23));
        spinBoxRefactDx->setDecimals(5);
        spinBoxRefactDx->setMaximum(100000);
        label = new QLabel(RefactFormDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 21, 21));
        label_2 = new QLabel(RefactFormDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 40, 21, 21));
        label_3 = new QLabel(RefactFormDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(270, 40, 21, 21));
        spinBoxRefactDy = new QDoubleSpinBox(RefactFormDialog);
        spinBoxRefactDy->setObjectName(QStringLiteral("spinBoxRefactDy"));
        spinBoxRefactDy->setGeometry(QRect(160, 40, 71, 23));
        spinBoxRefactDy->setDecimals(5);
        spinBoxRefactDy->setMaximum(100000);
        spinBoxRefactDz = new QDoubleSpinBox(RefactFormDialog);
        spinBoxRefactDz->setObjectName(QStringLiteral("spinBoxRefactDz"));
        spinBoxRefactDz->setGeometry(QRect(290, 40, 71, 23));
        spinBoxRefactDz->setDecimals(5);
        spinBoxRefactDz->setMaximum(100000);

        retranslateUi(RefactFormDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RefactFormDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RefactFormDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RefactFormDialog);
    } // setupUi

    void retranslateUi(QDialog *RefactFormDialog)
    {
        RefactFormDialog->setWindowTitle(QApplication::translate("RefactFormDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("RefactFormDialog", "dx", Q_NULLPTR));
        label_2->setText(QApplication::translate("RefactFormDialog", "dy", Q_NULLPTR));
        label_3->setText(QApplication::translate("RefactFormDialog", "dz", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RefactFormDialog: public Ui_RefactFormDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REFACTFORMDIALOG_H
