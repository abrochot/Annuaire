#ifndef PASSWORDHARDNESS_H
#define PASSWORDHARDNESS_H

#include <QWidget>

namespace Ui {
    class PasswordHardness;
}

class PasswordHardness : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordHardness(QWidget *parent = 0);
    ~PasswordHardness();

public slots:
    void newPasswordEntered(QString);

private:
    Ui::PasswordHardness *ui;
};

#endif // PASSWORDHARDNESS_H
