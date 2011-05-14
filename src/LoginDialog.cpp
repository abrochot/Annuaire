#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QCryptographicHash>
#include <QDebug>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::login()
{
    return ui->edtLogin->text();
}

QString LoginDialog::password()
{
    QString pass = ui->edtPassword->text()+"AZerGfg584dR;9#\\n";
    QString passCrypted = QString(QCryptographicHash::hash(pass.toAscii(),QCryptographicHash::Md5));
    qDebug() << passCrypted;
    return passCrypted;
}
