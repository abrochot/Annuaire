#include <QDebug>
#include "MySqlQueryModel.h"


MySqlQueryModel::MySqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}



void MySqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    QSqlQueryModel::setQuery(query,db);
    queryNonSorted = query.left(query.indexOf("ORDER BY")-1);
    columns.clear();
    QString queryTruncated = queryNonSorted;

    //on découpe la chaine pour n'avoir que les titres des colonnes :
    queryTruncated.remove(0,7);
    queryTruncated.remove(queryTruncated.indexOf(" FROM "),queryTruncated.length());
    //on stocke alors ces titres dans la liste Columns :


    columns = queryTruncated.split(QRegExp(","),QString::SkipEmptyParts );
    for (int i=0; i<columns.count(); i++)
	qDebug()<<columns[i];

    emit newQuery();
}


void MySqlQueryModel::sort(int column, Qt::SortOrder order)
{
    qDebug()<<"sort";
    QString newQuery=queryNonSorted;
    newQuery.append(" ORDER BY ");
    newQuery.append(columns[column]);
    if (order==Qt::DescendingOrder)
    {
	newQuery.append(" DESC");
    }

    setQuery(newQuery);


}
