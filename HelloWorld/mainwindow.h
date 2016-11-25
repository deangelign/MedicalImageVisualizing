#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "brightcontrastdialog.h"
#include "refactformdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void testeFunction();

private slots:
    void on_action3D_Image_triggered();
    void on_spinBoxImageZ_valueChanged(int arg1);

    void on_spinBoxImageY_valueChanged(int arg1);

    void on_spinBoxImageX_valueChanged(int arg1);

    void on_mirrorZ_clicked();

    void on_rotateZ_90AntiClockwise_clicked();

    void on_rotateY_90Anticlockwise_clicked();

    void on_rotateY_90Anticlockwise_2_clicked();

    void on_actionLabel_map_triggered();

    void on_labelFigureZ_customContextMenuRequested(const QPoint &pos);

    void on_labelFigureY_customContextMenuRequested(const QPoint &pos);

    void on_labelFigureX_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_clicked();
    void updateImagesNewBrightContrast();
    void displayNegativeImage();
    void displayNormalizedImage();
    void refactScene();

    void on_pushButton_2_clicked();

    void on_actionRefactor_triggered();

    void on_SpinBoxPointX_valueChanged(double arg1);

    void on_SpinBoxPointY_valueChanged(double arg1);

    void on_SpinBoxPointZ_valueChanged(double arg1);

    void on_SpinBoxVectorX_valueChanged(double arg1);

    void on_SpinBoxVectorY_valueChanged(double arg1);

    void on_SpinBoxVectorZ_valueChanged(double arg1);

    void on_actionGenerate_New_Volume_triggered();

    void on_labelFigureXYZ_customContextMenuRequested(const QPoint &pos);

    void on_doubleSpinBoxThetaX_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    BrightContrastDialog *brightContrastDialogForm;
    RefactFormDialog *refactFormDialog;

};

#endif // MAINWINDOW_H
