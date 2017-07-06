/********************************************************************************
** Form generated from reading UI file 'createvolumedialogform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEVOLUMEDIALOGFORM_H
#define UI_CREATEVOLUMEDIALOGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CreateVolumeDialogForm
{
public:
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QDoubleSpinBox *doubleSpinBox_3;
    QDoubleSpinBox *doubleSpinBox_4;
    QDoubleSpinBox *doubleSpinBox_5;
    QDoubleSpinBox *doubleSpinBox_6;
    QDoubleSpinBox *doubleSpinBox_7;
    QDoubleSpinBox *doubleSpinBox_8;
    QDoubleSpinBox *doubleSpinBox_9;

    void setupUi(QDialog *CreateVolumeDialogForm)
    {
        if (CreateVolumeDialogForm->objectName().isEmpty())
            CreateVolumeDialogForm->setObjectName(QStringLiteral("CreateVolumeDialogForm"));
        CreateVolumeDialogForm->resize(369, 241);
        buttonBox = new QDialogButtonBox(CreateVolumeDialogForm);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 200, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        doubleSpinBox = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(70, 50, 66, 23));
        doubleSpinBox_2 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(170, 50, 66, 23));
        doubleSpinBox_3 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        doubleSpinBox_3->setGeometry(QRect(260, 50, 66, 23));
        doubleSpinBox_4 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_4->setObjectName(QStringLiteral("doubleSpinBox_4"));
        doubleSpinBox_4->setGeometry(QRect(70, 90, 66, 23));
        doubleSpinBox_5 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_5->setObjectName(QStringLiteral("doubleSpinBox_5"));
        doubleSpinBox_5->setGeometry(QRect(170, 90, 66, 23));
        doubleSpinBox_6 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_6->setObjectName(QStringLiteral("doubleSpinBox_6"));
        doubleSpinBox_6->setGeometry(QRect(260, 90, 66, 23));
        doubleSpinBox_7 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_7->setObjectName(QStringLiteral("doubleSpinBox_7"));
        doubleSpinBox_7->setGeometry(QRect(70, 130, 66, 23));
        doubleSpinBox_8 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_8->setObjectName(QStringLiteral("doubleSpinBox_8"));
        doubleSpinBox_8->setGeometry(QRect(170, 130, 66, 23));
        doubleSpinBox_9 = new QDoubleSpinBox(CreateVolumeDialogForm);
        doubleSpinBox_9->setObjectName(QStringLiteral("doubleSpinBox_9"));
        doubleSpinBox_9->setGeometry(QRect(260, 130, 66, 23));

        retranslateUi(CreateVolumeDialogForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateVolumeDialogForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateVolumeDialogForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateVolumeDialogForm);
    } // setupUi

    void retranslateUi(QDialog *CreateVolumeDialogForm)
    {
        CreateVolumeDialogForm->setWindowTitle(QApplication::translate("CreateVolumeDialogForm", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CreateVolumeDialogForm: public Ui_CreateVolumeDialogForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEVOLUMEDIALOGFORM_H
