#pragma once
#include "FxCommonUIAPI.h"

#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>


class FX_COMMONUI_API FxDataTable : public QStandardItemModel
{
public:
    FxDataTable();
    FxDataTable( int rows, int cols );
    ~FxDataTable();

public:
    //static DataTable* fromTableView( QTableView* table, QStringList headers );
};

class FX_COMMONUI_API FxTableView : public QTableView
{
public:
    explicit FxTableView( QWidget* parent = nullptr );
    ~FxTableView();
    QStringList headers;
    FxDataTable* dataTable();
    void setHeaders( QStringList headers );
    void setRowCount( int count );
    QStandardItem* item( int row, int col );
    QStandardItem* item( int row, QString header );
    void setText( int row, int col, QString data );
    void setText( int row, QString header, QString data );

protected:
    void keyPressEvent( QKeyEvent* event );
};

