#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"
#include "LoginDialog.h"
#include "registerDialog.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QStringList>


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

    connect(ui->leRecherche,SIGNAL(textChanged(QString)),this,SLOT(recherche(QString)));

    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));

    db->setHostName("localhost");
    db->setPort(3306);
    db->setDatabaseName("test");
    db->setUserName("root");
    db->setPassword("root");

    if (!db->open())
    {
	QMessageBox::critical(0, QObject::tr("Database Error"), db->lastError().text());
    }

}

FenPrincipale::~FenPrincipale()
{
    delete ui;
    db->close();
    delete db;
}


void FenPrincipale::showAPropos()
{
    aPropos dialog(0);
    dialog.setWindowFlags(Qt::FramelessWindowHint);
    dialog.move(pos().x()+(width()-dialog.width())/2,pos().y()+(height()-dialog.height())/2);
    dialog.exec();
}


void FenPrincipale::connexion()
{

    LoginDialog dialog;
    dialog.setWindowFlags(Qt::FramelessWindowHint);
    dialog.move(pos().x()+(width()-dialog.width())/2,pos().y()+(height()-dialog.height())/2);
    if (dialog.exec()==QDialog::Accepted)
    {

	/*QSqlQuery insertQuery;

	insertQuery.prepare("UPDATE etudiants SET password=:password WHERE login=:login ");//AND password=:password");
	insertQuery.bindValue(":login",dialog.login());
	insertQuery.bindValue(":password", dialog.password());
	insertQuery.exec();
	*/

	QSqlQuery query;
	query.prepare("SELECT * FROM users WHERE login=:login && password=:password");
	query.bindValue(":login",dialog.login());
	query.bindValue(":password", dialog.password());

	query.exec();

	if (query.next())
	{
	    model = new MySqlQueryModel(this);
	    connect(model,SIGNAL(newQuery()),this,SLOT(miseAJourModel()));

	    ui->tableEtudiants->setModel(model);
	    model->setQuery("SELECT nom,prenom,numTel,mail1,mail2,cursus FROM etudiants",*db);

	    ui->actionD_connexion->setVisible(true);
	    ui->actionConnexion->setVisible(false);
	}
	else
	    QMessageBox::critical(this,"connexion échouée","Le nom d'utilisateur ou le mot de passe est incorrect",QMessageBox::Ok);

    }
}

void FenPrincipale::deconnexion()
{
    model->clear();
    delete model;
    ui->tableEtudiants->setModel(NULL);
    ui->actionD_connexion->setVisible(false);
    ui->actionConnexion->setVisible(true);
}

void FenPrincipale::nouvelUtilisateur()
{
    // On récupère la liste des écoles, afin de proposer les choix dans une combobox sur la fenêtre d'enregistrement
    QSqlQuery listesQuery;
    listesQuery.exec("SELECT Nom FROM ecoleArchi");

    QStringList listeEcole;

    while (listesQuery.next())
    {
	listeEcole << listesQuery.value(0).toString();
    }

    listesQuery.exec("SELECT Nom FROM entreprise");

    QStringList listeEntreprises;

    while(listesQuery.next())
    {
	listeEntreprises << listesQuery.value(0).toString();
    }

    registerDialog dialog(listeEcole,listeEntreprises);



    bool errors = true;


    while (dialog.exec()==QDialog::Accepted && errors)
    {


	infoUser infos = dialog.getUserInfo();

	QSqlQuery query;
	query.prepare("SELECT * FROM Users WHERE login=:login;");
	query.bindValue(":login",infos.login);
	query.exec();



	if (query.next())
	{
	    errors = true;
	    QMessageBox::critical(this,"Erreur lors de l'enregistrement","Le nom d'utilisateur est déjà pris",QMessageBox::Ok);
	}
	else
	{

	    //tout est correct, on entre l'utilisateur dans la base.

	    //on commence par rajouter l'ecole et l'entreprise afin d'avoir les clés étrangères dans Etudiant
	    int ecoleId = registerEcole(infos.EcoleArchi);
	    int entrepriseId = registerEntreprise(infos.Entreprise);

	    QSqlQuery registerQuery;
	    registerQuery.prepare("INSERT INTO users(login, password, account) VALUES (:login, :password, \"user\")");
	    registerQuery.bindValue(":login",infos.login);
	    registerQuery.bindValue(":password",infos.password);
	    registerQuery.exec();

	    //on commence par trouver la clé user générée afin de la mettre en clé étrangère dans etudiants

	    registerQuery.prepare("SELECT idUser FROM users WHERE login=:login");
	    registerQuery.bindValue(":login",infos.login);
	    registerQuery.exec();

	    registerQuery.next();


	    int userId = registerQuery.value(0).toInt();


	    // On peut enfin ajouter l'étudiant :
	    QString queryStr;
	    queryStr = "INSERT INTO etudiants(";
	    queryStr.append("idUser, Nom, Prenom, NumTel, mail1, mail2, Cursus, AnneeDiplomeINSA, AnneeDiplomeARCHI");
	    queryStr.append(", Type, idEcoleArchi, idEntreprise)");
	    queryStr.append(" VALUES (");
	    queryStr.append(":idUsers, :Nom, :Prenom, :NumTel, :mail1, :mail2, :Cursus, :AnneeDiplomeINSA, :AnneeDiplomeARCHI");
	    queryStr.append(", :Type, :idEcoleArchi, :idEntreprise)");

	    registerQuery.prepare(queryStr);
	    registerQuery.bindValue(":idUsers",userId);
	    registerQuery.bindValue(":Nom",infos.nom);
	    registerQuery.bindValue(":Prenom",infos.prenom);
	    registerQuery.bindValue(":NumTel",infos.numTel);
	    registerQuery.bindValue(":mail1",infos.mail1);
	    registerQuery.bindValue(":mail2",infos.mail2);
	    registerQuery.bindValue(":Cursus",infos.cursus);
	    registerQuery.bindValue(":AnneeDiplomeINSA",infos.anneeDiplomeINSA);
	    registerQuery.bindValue(":AnneeDiplomeARCHI",infos.anneeDiplomeARCHI);
	    registerQuery.bindValue(":Type",infos.type);
	    registerQuery.bindValue(":idEcoleArchi",ecoleId);
	    registerQuery.bindValue(":idEntreprise",entrepriseId);

	    registerQuery.exec();

	    QMessageBox::information(this,"Enregistrement réussi","Vous êtes maintenant enregistré<br> vous pouvez désormais vous connecter avec votre login/mot de passe",QMessageBox::Ok);
	    break;
	}
    }
}

void FenPrincipale::miseAJourModel()
{
    for (int i=0; i<model->rowCount();i++)
	ui->tableEtudiants->setRowHeight(i, 18);
}


int FenPrincipale::registerEntreprise(QString entreprise)
{
    QSqlQuery query;
    query.prepare("SELECT idEntreprise FROM entreprise WHERE Nom=:nomEntreprise");
    query.bindValue(":nomEntreprise",entreprise);
    query.exec();
    if (!query.next())
    {
	// l'entreprise n'a pas été trouvée :
	// il faut d'abord ajouter l'entreprise à la base pour ensuite récupérer son id
	query.prepare("INSERT INTO entreprise(Nom) VALUES (:nomEntreprise)");
	query.bindValue(":nomEntreprise",entreprise);
	query.exec();

	query.prepare("SELECT idEntreprise FROM entreprise WHERE Nom=:nomEntreprise");
	query.bindValue(":nomEntreprise",entreprise);
	query.exec();
	query.next();
    }

    return query.value(0).toInt();
}

int FenPrincipale::registerEcole(QString ecole)
{
    QSqlQuery query;
    query.prepare("SELECT idEcoleArchi FROM ecoleArchi WHERE Nom=:nomEcole");
    query.bindValue(":nomEcole",ecole);
    query.exec();
    if (!query.next())
    {
	// l'entreprise n'a pas été trouvée :
	// il faut d'abord ajouter l'entreprise à la base pour ensuite récupérer son id
	query.prepare("INSERT INTO ecoleArchi(Nom) VALUES (:nomEcole)");
	query.bindValue(":nomEcole",ecole);
	query.exec();

	query.prepare("SELECT idEcoleArchi FROM ecoleArchi WHERE Nom=:nomEcole");
	query.bindValue(":nomEcole",ecole);
	query.exec();
    }


    return query.value(0).toInt();

}

void FenPrincipale::recherche(QString newText)
{
    for (int i=0; i<model->rowCount(); i++)
    {
	int refCount=0;
	for(int j=0; j<model->columnCount();j++)
	{
	    qDebug()<<i << " " << j;
	    qDebug()<<model->data(model->index(i,j)).toString();
	    if (model->data(model->index(i,j)).toString().contains(newText,Qt::CaseInsensitive))
	    {
		refCount++;
		ui->tableEtudiants->showRow(i);
		break;
	    }
	}
	if (refCount==0)
	    ui->tableEtudiants->hideRow(i);
    }
}
