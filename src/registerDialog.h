#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

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
    QString annesDiplomeARCHI;
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
    ~registerDialog();
    infoUser getUserInfo();
private:
    Ui::registerDialog *ui;
};

#endif // REGISTERDIALOG_H
