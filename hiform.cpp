#include "hiform.h"
#include "ui_hiform.h"

HiForm::HiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HiForm)
{
    ui->setupUi(this);
}

HiForm::~HiForm()
{
    delete ui;
}

void HiForm::on_pushButton_clicked()
{
    close();
}
