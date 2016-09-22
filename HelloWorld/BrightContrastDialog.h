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
    explicit BrightContrastDialog(QWidget *parent = 0);
    ~BrightContrastDialog();

private:
    Ui::BrightContrastDialog *ui;
};

#endif // BRIGHTCONTRASTDIALOG_H
