/********************************************************************************
** Form generated from reading UI file 'dialogtest.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTEST_H
#define UI_DIALOGTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DialogTest
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogTest)
    {
        if (DialogTest->objectName().isEmpty())
            DialogTest->setObjectName(QStringLiteral("DialogTest"));
        DialogTest->resize(240, 320);
        buttonBox = new QDialogButtonBox(DialogTest);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(10, 270, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(DialogTest);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogTest, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogTest, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogTest);
    } // setupUi

    void retranslateUi(QDialog *DialogTest)
    {
        DialogTest->setWindowTitle(QApplication::translate("DialogTest", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogTest: public Ui_DialogTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTEST_H
