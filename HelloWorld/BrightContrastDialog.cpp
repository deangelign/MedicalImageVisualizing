#include "BrightContrastDialog.h"
#include "ui_brightContrastDialog.h"

BrightContrastDialog::BrightContrastDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrightContrastDialog)
{
    ui->setupUi(this);
}


BrightContrastDialog::~BrightContrastDialog()
{
    delete ui;
}
