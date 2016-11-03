#ifndef CREATEVOLUMEDIALOGFORM_H
#define CREATEVOLUMEDIALOGFORM_H

#include <QDialog>

namespace Ui {
class CreateVolumeDialogForm;
}

class CreateVolumeDialogForm : public QDialog
{
    Q_OBJECT

public:
    explicit CreateVolumeDialogForm(QWidget *parent = 0);
    ~CreateVolumeDialogForm();

private:
    Ui::CreateVolumeDialogForm *ui;
};

#endif // CREATEVOLUMEDIALOGFORM_H
