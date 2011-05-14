#include "aPropos.h"
#include "ui_aPropos.h"

aPropos::aPropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aPropos)
{
    ui->setupUi(this);
}

aPropos::~aPropos()
{
    delete ui;
}
