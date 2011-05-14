#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <aPropos.h>


namespace Ui {
    class FenPrincipale;
}

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenPrincipale(QWidget *parent = 0);
    ~FenPrincipale();


public slots:
    void showAPropos();
    void deconnexion();
    void connexion();




private:
    Ui::FenPrincipale *ui;
    QSqlDatabase *db;
    QSqlQueryModel *model;

};

#endif // FENPRINCIPALE_H
