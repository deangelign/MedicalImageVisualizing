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
    explicit PhongOptions(QWidget *parent = 0);
    ~PhongOptions();

private:
    Ui::PhongOptions *ui;
};

#endif // PHONGOPTIONS_H
