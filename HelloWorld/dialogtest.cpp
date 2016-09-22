#include "dialogtest.h"
#include "ui_dialogtest.h"

DialogTest::DialogTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTest)
{
    ui->setupUi(this);
}

DialogTest::~DialogTest()
{
    delete ui;
}
