#ifndef TABLEWIDGETUTILS_H
#define TABLEWIDGETUTILS_H

#include <QMap>
#include <QList>
#include <QTableWidget>

class TableWidgetUtils
{
public:
    TableWidgetUtils();

    static QMap<QString, QList<double>> GetTableDataByColumn(const QTableWidget* tableWidget,int startColumnIndex);
};

#endif // TABLEWIDGETUTILS_H
