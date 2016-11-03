#include "createvolumedialogform.h"
#include "ui_createvolumedialogform.h"

CreateVolumeDialogForm::CreateVolumeDialogForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateVolumeDialogForm)
{
    ui->setupUi(this);
}

CreateVolumeDialogForm::~CreateVolumeDialogForm()
{
    delete ui;
}
