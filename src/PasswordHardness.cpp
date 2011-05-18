#include "PasswordHardness.h"
#include "ui_PasswordHardness.h"

PasswordHardness::PasswordHardness(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordHardness)
{
    ui->setupUi(this);
}

PasswordHardness::~PasswordHardness()
{
    delete ui;
}


void PasswordHardness::newPasswordEntered(QString password)
{
    int hardness = 0;

    if (password.length()>6)
	hardness+=5;
    if (password.length()>10)
	hardness+=3;

    int currentRep = 0;
    int maxRep=0;
    int hasDigit   = 0;
    int hasMaj     = 0;
    int hasSpecial = 0;

    QChar character = password[0];
    for(int i=0; i<password.length(); i++)
    {
	if (character == password[i])
	    currentRep++;
	else
	{
	    character = password[i];
	    if (currentRep>maxRep)
		maxRep = currentRep;
	}
	if (password[i].isUpper())
	    hasMaj=1;
	if (password[i].isDigit())
	    hasDigit=1;
	if (!password[i].isLetterOrNumber())
	    hasSpecial=1;
    }

    if (maxRep == 1)
	hardness+=2;

    hardness += 3*(hasDigit + hasMaj + hasSpecial);

    ui->pbHardness->setValue(hardness);

    QString pbStyleSheet ="QProgressBar:horizontal { background: white;	border-radius : 1px }";
    pbStyleSheet.append("QProgressBar::chunk:horizontal {");

    if (hardness<5)
    {
	    pbStyleSheet.append("background:red;}");
	    ui->lbHardness->setText("mot de passe faible");
    }
    else
	if (hardness<10)
	{
	    pbStyleSheet.append("background:orange;}");
	    ui->lbHardness->setText("mot de passe moyen");
	} else
	    if (hardness<15)
	    {
		pbStyleSheet.append("background:green;}");
		ui->lbHardness->setText("mot de passe fort");
	    } else
	    {
		pbStyleSheet.append("background:blue;}");
		ui->lbHardness->setText("mot de passe très fort");
	    }
    ui->pbHardness->setStyleSheet(pbStyleSheet);
}
