#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
