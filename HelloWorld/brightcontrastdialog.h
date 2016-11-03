#ifndef BRIGHTCONTRASTDIALOG_H
#define BRIGHTCONTRASTDIALOG_H

#include <QDialog>

namespace Ui {
class BrightContrastDialog;
}

class BrightContrastDialog : public QDialog
{
    Q_OBJECT

public:
    int brightPercetage;
    int contrastPercetage;
    float brightValue;
    float contrastValue;
    float maximumValue;
    bool negative;
    bool normalization;


    explicit BrightContrastDialog(QWidget *parent = 0);
    BrightContrastDialog(QWidget *parent,float brightValue,float contrastValue,float maximumValue, bool negative,bool normalization);
    ~BrightContrastDialog();

private slots:
    void on_horizontalSliderBrightDIalog_valueChanged(int value);

    void on_horizontalSliderContrastDialog_valueChanged(int value);

    void on_checkBoxNormalizacao_toggled(bool checked);

    void on_checkBoxNegativo_toggled(bool checked);

    void on_spinBoxBright_valueChanged(int arg1);

    void on_spinBoxContrast_valueChanged(int arg1);

    void on_checkBoxLimiarizacao_toggled(bool checked);

signals:
    void brightSignal(float brightValue);
    void contrastSignal(float contrast);
    void negativeSignal(bool negative);
    void normalizationSignal(bool normalization);


private:
    Ui::BrightContrastDialog *ui;
};

#endif // BRIGHTCONTRASTDIALOG_H
