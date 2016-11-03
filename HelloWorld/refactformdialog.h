#ifndef REFACTFORMDIALOG_H
#define REFACTFORMDIALOG_H

#include <QDialog>

namespace Ui {
class RefactFormDialog;
}

class RefactFormDialog : public QDialog
{
    Q_OBJECT

public:
    float dx;
    float dy;
    float dz;

    explicit RefactFormDialog(QWidget *parent = 0);
    RefactFormDialog(QWidget *parent,float dx,float dy,float dz);
    ~RefactFormDialog();

signals:
    void okSignal(float dx,float dy,float dz);

private slots:
    void on_buttonBox_accepted();

    void on_spinBoxRefactDx_valueChanged(double dx);

    void on_spinBoxRefactDy_valueChanged(double dy);

    void on_spinBoxRefactDz_valueChanged(double dz);

private:
    Ui::RefactFormDialog *ui;
};

#endif // REFACTFORMDIALOG_H
