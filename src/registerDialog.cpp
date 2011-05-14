#include "registerDialog.h"
#include "ui_registerDialog.h"

registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
}

registerDialog::~registerDialog()
{
    delete ui;
}





infoUser registerDialog::getUserInfo()
{
    infoUser infos;

    infos.login = ui->leLogin->text();
    infos.password = ui->lePassword->text();

    infos.nom = ui->leNom->text();
    infos.prenom = ui->lePrenom->text();
    infos.numTel = ui->leNumTel->text();
    infos.mail1 = ui->leMail1->text();
    infos.mail2 = ui->leMail2->text();

    infos.cursus = ui->cbCursus->currentText();
    infos.anneeDiplomeINSA = ui->leAnneeDiplomeINSA->text();
    infos.annesDiplomeARCHI = ui->leAnneeDiplomeARCHI->text();
    infos.type = ui->leType->text();
    infos.EcoleArchi = ui->leEcoleArchi->text();

    infos.Entreprise = ui->leEntreprise->text();
    infos.Pays = ui->lePays->text();


    return infos;


}
