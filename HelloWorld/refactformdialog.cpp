#include "refactformdialog.h"
#include "ui_refactformdialog.h"

RefactFormDialog::RefactFormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefactFormDialog)
{
    ui->setupUi(this);
}
RefactFormDialog::RefactFormDialog(QWidget *parent,float dx,float dy,float dz):
    QDialog(parent),
    ui(new Ui::RefactFormDialog){

    ui->setupUi(this);
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
    ui->spinBoxRefactDx->setValue(dx);
    ui->spinBoxRefactDy->setValue(dy);
    ui->spinBoxRefactDz->setValue(dz);

}

RefactFormDialog::~RefactFormDialog()
{
    delete ui;
}

void RefactFormDialog::on_buttonBox_accepted()
{
    emit okSignal(this->dx,this->dy,this->dz);
}

void RefactFormDialog::on_spinBoxRefactDx_valueChanged(double dx)
{
    this->dx = dx;
}

void RefactFormDialog::on_spinBoxRefactDy_valueChanged(double dy)
{
    this->dy = dy;
}

void RefactFormDialog::on_spinBoxRefactDz_valueChanged(double dz)
{
    this->dz = dz;
}
