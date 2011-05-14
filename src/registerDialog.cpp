#include <QList>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
#include "registerDialog.h"
#include "ui_registerDialog.h"


registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
}

registerDialog::registerDialog(QStringList listeEcole, QStringList listeEntreprise, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::registerDialog)

{
    ui->setupUi(this);

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(OkClicked()));


    champsRequis << ui->leLogin;
    champsRequis << ui->lePassword;
    champsRequis << ui->lePassword2;
    champsRequis << ui->leNom;
    champsRequis << ui->lePrenom;
    champsRequis << ui->leMail1;
    champsRequis << ui->leAnneeDiplomeINSA;
    champsRequis << ui->leAnneeDiplomeARCHI;
    champsRequis << ui->leType;

    ui->cbEcole->addItems(listeEcole);
    ui->cbEntreprise->addItems(listeEntreprise);
}

registerDialog::~registerDialog()
{
    delete ui;
}





infoUser registerDialog::getUserInfo()
{
    infoUser infos;

    infos.login = ui->leLogin->text();
    // on crypte le mot de passe avant de l'envoyer à la base
    //ajout d'un aléa
    QString pass = ui->lePassword->text()+"AZerGfg584dR;9#\\n";
    //génération du hash md5
    QString passCrypted = QString(QCryptographicHash::hash(pass.toAscii(),QCryptographicHash::Md5));

    infos.password = passCrypted;
    qDebug() << passCrypted;

    infos.nom = ui->leNom->text();
    infos.prenom = ui->lePrenom->text();
    infos.numTel = ui->leNumTel->text();
    infos.mail1 = ui->leMail1->text();
    infos.mail2 = ui->leMail2->text();

    infos.cursus = ui->cbCursus->currentText();
    infos.anneeDiplomeINSA = ui->leAnneeDiplomeINSA->text();
    infos.anneeDiplomeARCHI = ui->leAnneeDiplomeARCHI->text();
    infos.type = ui->leType->text();
    infos.EcoleArchi = ui->cbEcole->currentText();

    infos.Entreprise = ui->cbEntreprise->currentText();
    infos.Pays = ui->lePays->text();


    return infos;


}

void registerDialog::OkClicked()
{
    QString errorMsg = "";

    if (ui->cbEcole->currentText().isEmpty())
    {
	errorMsg = "Certains champs requis sont vides<br>";
	ui->cbEcole->setStyleSheet("border: 2px solid red;");
    }
    else
	ui->cbEcole->setStyleSheet("");

    for (QList<QLineEdit*>::iterator it=champsRequis.begin(); it!=champsRequis.end(); it++)
    {

	if ((*it)->text().isEmpty())
	{
	    errorMsg = "Certains champs requis sont vides<br>";
	    (*it)->setStyleSheet("border: 2px solid red;");
	} else
	    (*it)->setStyleSheet("");
    }


    if (ui->lePassword->text() != ui->lePassword2->text())
	errorMsg.append("La confirmation du mot de passe est incorrecte<br>");

    if (errorMsg.isEmpty())
	accept();
    else
	QMessageBox::critical(this,"Erreur lors de l'enregistrement",errorMsg,QMessageBox::Ok);

}
