#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>

#include "MySqlQueryModel.h"
#include "aPropos.h"


namespace Ui {
    class FenPrincipale;
}

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenPrincipale(QWidget *parent = 0);
    ~FenPrincipale();
    int registerEntreprise(QString entreprise);
    int registerEcole(QString ecole);

public slots:
    void showAPropos();
    void deconnexion();
    void connexion();
    void nouvelUtilisateur();
    void miseAJourModel();



private:
    Ui::FenPrincipale *ui;
    QSqlDatabase *db;
    MySqlQueryModel *model;

};

#endif // FENPRINCIPALE_H
