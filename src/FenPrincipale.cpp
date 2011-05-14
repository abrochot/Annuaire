#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"
#include "LoginDialog.h"
#include "registerDialog.h"
#include <QCryptographicHash>
#include <QMessageBox>

FenPrincipale::FenPrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenPrincipale)
{
    ui->setupUi(this);

    connect(ui->actionA_Propos,SIGNAL(triggered()),this,SLOT(showAPropos()));
    connect(ui->actionQuitter,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionD_connexion,SIGNAL(triggered()),this, SLOT(deconnexion()));
    connect(ui->actionConnexion,SIGNAL(triggered()),this, SLOT(connexion()));
    connect(ui->actionNouvel_utilisateur,SIGNAL(triggered()),this,SLOT(nouvelUtilisateur()));


    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));

}

FenPrincipale::~FenPrincipale()
{
    delete ui;
    db->close();
    delete db;
}


void FenPrincipale::showAPropos()
{
    aPropos fen(this);
    fen.exec();
}


void FenPrincipale::connexion()
{
    db->close();

    db->setHostName("localhost");
    db->setPort(3306);
    db->setDatabaseName("test");
    db->setUserName("root");
    db->setPassword("root");

    if (!db->open())
    {
	QMessageBox::critical(0, QObject::tr("Database Error"), db->lastError().text());
    }



    LoginDialog dialog(this);


    if (dialog.exec()==QDialog::Accepted)
    {

	/*QSqlQuery insertQuery;

	insertQuery.prepare("UPDATE etudiants SET password=:password WHERE login=:login ");//AND password=:password");
	insertQuery.bindValue(":login",dialog.login());
	insertQuery.bindValue(":password", dialog.password());
	insertQuery.exec();
*/

	QSqlQuery query;
	query.prepare("SELECT * FROM etudiants WHERE login=:login && password=:password");
	query.bindValue(":login",dialog.login());
	query.bindValue(":password", dialog.password());

	query.exec();
	if (query.next())
	    QMessageBox::information(this,"connexion réussie","Vous êtes maintenant connecté",QMessageBox::Ok);
	else
	    QMessageBox::critical(this,"connexion échouée",dialog.password(),QMessageBox::Ok);
	/*while(query.first())
	{
	int id = query.value(0).toInt();
	QString nom = query.value(1).toString();
	QMessageBox::information (0, QObject::tr("Information récupérée"), "Id : " + QString::number(id) + "\nNom : " + nom);
	}*/
    }




    model = new QSqlQueryModel(this);

    model->setQuery("SELECT * FROM etudiants");
    ui->tableEtudiants->setModel(model);

    ui->actionD_connexion->setVisible(true);
    ui->actionConnexion->setVisible(false);

}

void FenPrincipale::deconnexion()
{
    db->close();
    model->clear();
    ui->actionD_connexion->setVisible(false);
    ui->actionConnexion->setVisible(true);
}

void FenPrincipale::nouvelUtilisateur()
{
    registerDialog dialog(this);


    bool errors = true;

    while (dialog.exec()==QDialog::Accepted && errors)
    {
	QSqlQuery query;
	query.prepare("SELECT * FROM etudiants WHERE login=:login");
	query.bindValue(":login","login");
	query.exec();

	if (query.next())
	{

	    QMessageBox::critical(this,"Erreur lors de l'enregistrement","Le nom d'utilisateur est déjà pris",QMessageBox::Ok);
	}
	else
	    QMessageBox::information(this,"Enregistrement réussi","Vous êtes maintenant enregistré<br> vous pouvez désormais vous connecter avec votre login/mot de passe",QMessageBox::Ok);

    }



}
