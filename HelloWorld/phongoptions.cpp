#include "phongoptions.h"
#include "ui_phongoptions.h"

PhongOptions::PhongOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhongOptions)
{
    ui->setupUi(this);
}

PhongOptions::~PhongOptions()
{
    delete ui;
}
