#ifndef MYSQLQUERYMODEL_H
#define MYSQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QStringList>

class MySqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit MySqlQueryModel(QObject *parent = 0);
    void setQuery(const QString &query, const QSqlDatabase &db=QSqlDatabase());
    void sort(int column, Qt::SortOrder order);
signals:
    void newQuery();
public slots:

private:
    QString queryNonSorted;
    QStringList columns;
};

#endif // MYSQLQUERYMODEL_H
