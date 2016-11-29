#ifndef PHONGOPTIONS_H
#define PHONGOPTIONS_H

#include <QDialog>

namespace Ui {
class PhongOptions;
}

class PhongOptions : public QDialog
{
    Q_OBJECT

public:
    float x_a;
    float y_a;
    float z_a;
    float alpha_a;
    float ka;

    float x_d;
    float y_d;
    float z_d;
    float alpha_d;
    float kd;

    float x_s;
    float y_s;
    float z_s;
    float alpha_s;
    float ks;

    float shininess;


    explicit PhongOptions(QWidget *parent = 0);
    ~PhongOptions();

private:
    Ui::PhongOptions *ui;
};

#endif // PHONGOPTIONS_H
