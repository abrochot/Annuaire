#ifndef APROPOS_H
#define APROPOS_H

#include <QDialog>

namespace Ui {
    class aPropos;
}

class aPropos : public QDialog
{
    Q_OBJECT

public:
    explicit aPropos(QWidget *parent = 0);
    ~aPropos();

private:
    Ui::aPropos *ui;
};

#endif // APROPOS_H
