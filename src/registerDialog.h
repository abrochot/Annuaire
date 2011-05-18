#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "PasswordHardness.h"
namespace Ui {
    class registerDialog;
}

// toutes les informations entrées dans les formulaires
typedef struct {
    QString login;
    QString password;

    QString nom;
    QString prenom;
    QString numTel;
    QString mail1;
    QString mail2;

    QString cursus;
    QString anneeDiplomeINSA;
    QString anneeDiplomeARCHI;
    QString type;
    QString EcoleArchi;

    QString Entreprise;
    QString Pays;
} infoUser;


class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = 0);
    registerDialog(QStringList listeEcole, QStringList listeEntreprises, QWidget *parent = 0);
    ~registerDialog();
    infoUser getUserInfo();

public slots:
    void OkClicked();

private:
    Ui::registerDialog *ui;
    QList<QLineEdit *> champsRequis;
};

#endif // REGISTERDIALOG_H
