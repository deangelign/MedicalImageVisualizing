#include "brightcontrastdialog.h"
#include "ui_brightcontrastdialog.h"

BrightContrastDialog::BrightContrastDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrightContrastDialog)
{
    ui->setupUi(this);
}

BrightContrastDialog::BrightContrastDialog(QWidget *parent,float brightValue,float contrastValue,float maximumValue,bool negative,bool normalization) :
    QDialog(parent),
    ui(new Ui::BrightContrastDialog)
{
    ui->setupUi(this);
    this->brightValue = brightValue;
    this->contrastValue = contrastValue;
    this->maximumValue = maximumValue;
    this->brightPercetage = round((this->brightValue/maximumValue)*100);
    this->contrastPercetage = round((this->contrastValue/maximumValue)*100);
    ui->horizontalSliderBrightDIalog->setValue(100-this->brightPercetage);
    ui->horizontalSliderContrastDialog->setValue(100-this->contrastPercetage);
    this->negative = negative;
    ui->checkBoxNegativo->setChecked(negative);
    this->normalization = normalization;
    ui->checkBoxNormalizacao->setChecked(normalization);
    ui->spinBoxBright->setValue(ui->horizontalSliderBrightDIalog->value());
}

BrightContrastDialog::~BrightContrastDialog()
{
    delete ui;
}



void BrightContrastDialog::on_horizontalSliderBrightDIalog_valueChanged(int value)
{
    this->brightValue = (100-value)*this->maximumValue/100;
    ui->spinBoxBright->setValue(value);
    emit brightSignal(this->brightValue);
    emit contrastSignal(this->contrastValue);
}



void BrightContrastDialog::on_horizontalSliderContrastDialog_valueChanged(int value)
{

<<<<<<< HEAD
    this->contrastValue = (value)*this->maximumValue/100;
=======
    this->contrastValue = (100-value)*this->maximumValue/100;
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58
    ui->spinBoxContrast->setValue(value);
    emit brightSignal(this->brightValue);
    emit contrastSignal(this->contrastValue);
}



void BrightContrastDialog::on_checkBoxNormalizacao_toggled(bool checked)
{
    if(checked == true){
        ui->checkBoxNegativo->setEnabled(false);
        ui->horizontalSliderBrightDIalog->setEnabled(false);
        ui->horizontalSliderContrastDialog->setEnabled(false);
        ui->spinBoxBright->setEnabled(false);
        ui->spinBoxLimiarizacao->setEnabled(false);
        ui->checkBoxLimiarizacao->setEnabled(false);
        this->normalization = true;
        emit normalizationSignal(true);
    }else{
        ui->checkBoxNegativo->setEnabled(true);
        ui->horizontalSliderBrightDIalog->setEnabled(true);
        ui->horizontalSliderContrastDialog->setEnabled(true);
        ui->spinBoxBright->setEnabled(true);
        ui->spinBoxLimiarizacao->setEnabled(true);
        ui->checkBoxLimiarizacao->setEnabled(true);
        this->normalization = false;
        emit normalizationSignal(false);
    }
}

void BrightContrastDialog::on_checkBoxNegativo_toggled(bool checked)
{
    if(checked == true){
        ui->checkBoxNormalizacao->setEnabled(false);
        ui->horizontalSliderBrightDIalog->setEnabled(false);
        ui->horizontalSliderContrastDialog->setEnabled(false);
        ui->spinBoxBright->setEnabled(false);
        ui->spinBoxLimiarizacao->setEnabled(false);
        ui->checkBoxLimiarizacao->setEnabled(false);
        this->negative = true;
        emit negativeSignal(true);
    }else{
        ui->checkBoxNormalizacao->setEnabled(true);
        ui->horizontalSliderBrightDIalog->setEnabled(true);
        ui->horizontalSliderContrastDialog->setEnabled(true);
        ui->spinBoxBright->setEnabled(true);
        ui->spinBoxLimiarizacao->setEnabled(true);
        ui->checkBoxLimiarizacao->setEnabled(true);
        this->negative = false;
        emit negativeSignal(false);
    }
}


void BrightContrastDialog::on_spinBoxBright_valueChanged(int value)
{
    ui->horizontalSliderBrightDIalog->setValue(value);
    this->brightValue = (100-value)*this->maximumValue/100;
    emit brightSignal(this->brightValue);
    //emit contrastSignal(this->contrastValue);
}

void BrightContrastDialog::on_spinBoxContrast_valueChanged(int value)
{
    ui->horizontalSliderContrastDialog->setValue(value);
<<<<<<< HEAD
    this->contrastValue = (value)*this->maximumValue/100;
=======
    this->contrastValue = (100-value)*this->maximumValue/100;
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58
    //emit brightSignal(this->brightValue);
    emit contrastSignal(this->contrastValue);
}

void BrightContrastDialog::on_checkBoxLimiarizacao_toggled(bool checked)
{

}
