#include "tablewidgetutils.h"

TableWidgetUtils::TableWidgetUtils()
{

}

QMap<QString, QList<double> > TableWidgetUtils::GetTableDataByColumn(const QTableWidget *tableWidget, int startColumnIndex)
{
    QMap<QString, QList<double>> dataMap;

    int columnCount = tableWidget->columnCount();
    int rowCount = tableWidget->rowCount();

    for (int column = startColumnIndex; column < columnCount; ++column)
    {
        QString columnName = tableWidget->horizontalHeaderItem(column)->text();
        QList<double> columnData;

        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem* item = tableWidget->item(row, column);
            if (item != nullptr) {
                bool ok;
                double value = item->text().toDouble(&ok);
                if (ok) {
                    columnData.append(value);
                }
            }
        }
        dataMap.insert(columnName, columnData);
    }
    return dataMap;
}
