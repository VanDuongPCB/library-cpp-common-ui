#include "FxTableView.h"
#include <QKeyEvent>

FxDataTable::FxDataTable() : QStandardItemModel( nullptr )
{

}

FxDataTable::FxDataTable( int rows, int cols ) : QStandardItemModel( rows, cols, nullptr )
{

}

FxDataTable::~FxDataTable()
{

}
//////////////////////////////////////////////////////////////////////////////////////////

FxTableView::FxTableView( QWidget* parent ) : QTableView( parent )
{
}

FxTableView::~FxTableView()
{
}


void FxTableView::keyPressEvent( QKeyEvent* event )
{
    QTableView::keyPressEvent( event );
    int key = event->key();
    // up + down
    if ( key == 16777235 || key == 16777237 )
    {
        emit pressed( this->currentIndex() );
    }
}

FxDataTable* FxTableView::dataTable()
{
    FxDataTable* m = ( FxDataTable* )this->model();
    if ( m == nullptr )
    {
        m = new FxDataTable();
        this->setModel( m );
    }
    return m;
}

void FxTableView::setHeaders( QStringList headers )
{
    this->headers = headers;
    FxDataTable* m = dataTable();
    m->setColumnCount( headers.size() );
    m->setHorizontalHeaderLabels( headers );
}

void FxTableView::setRowCount( int count )
{
    dataTable()->setRowCount( count );
}

QStandardItem* FxTableView::item( int row, int col )
{
    return ( ( QStandardItemModel* )model() )->item( row, col );
}

QStandardItem* FxTableView::item( int row, QString header )
{
    for ( int i = 0; i < headers.size(); i++ )
    {
        if ( header == headers[ i ] )
        {
            return ( ( QStandardItemModel* )model() )->item( row, i );
        }
    }
    return nullptr;
}

void FxTableView::setText( int row, int col, QString data )
{
    FxDataTable* m = dataTable();
    if ( row < 0 || row >= m->rowCount() ) return;
    if ( col < 0 || col >= m->columnCount() ) return;
    QStandardItem* item = ( QStandardItem* )m->item( row, col );
    if ( item == nullptr )
    {
        item = new QStandardItem();
        m->setItem( row, col, item );
    }
    item->setText( data );
}

void FxTableView::setText( int row, QString header, QString data )
{
    FxDataTable* m = dataTable();
    if ( row < 0 || row >= m->rowCount() ) return;
    for ( int col = 0; col < headers.size(); col++ )
    {
        if ( headers[ col ] == header )
        {
            setText( row, col, data );
            break;
        }
    }
}