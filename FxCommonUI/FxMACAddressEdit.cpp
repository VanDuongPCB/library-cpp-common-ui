#include "FxMACAddressEdit.h"

FxMacAddressEdit::FxMacAddressEdit( QWidget* parent ) : QLineEdit( parent )
{
    setInputMask( "HH-HH-HH-HH-HH-HH; " );
    QFont currentFont = font();
    currentFont.setCapitalization( QFont::AllUppercase );
    setFont( currentFont );

    connect( this, &FxMacAddressEdit::textChanged, this, &FxMacAddressEdit::CheckMAC );
}

FxMacAddressEdit::~FxMacAddressEdit()
{
}

void FxMacAddressEdit::CheckMAC( const QString& text )
{
    QString mac = text;
    mac = mac.replace( " ", "" ).replace( "-", "" );
    qDebug() << mac;
    if ( mac.isEmpty() )
    {
        setStyleSheet( "" );
        return;
    }
        
    if ( mac.length() != 12 )
    {
        setStyleSheet( "color:red" );
    }
    else
    {
        setStyleSheet( "" );
    }
}

const QString FxMacAddressEdit::GetMacAddress() const
{
    QString mac = text();
    mac = mac.replace( " ", "" ).replace( "-", "" );
    return mac.length() == 12 ? mac : "";
}

void FxMacAddressEdit::SetMacAddress( const QString& mac )
{
    QStringList items;
    for ( int i=0;i< mac.length(); i++ )
    {
        items.push_back( mac[ i ] );
        if ( i % 2 == 0 )
            items.push_back( "" );
        if ( i == 12 ) 
            break;
    }
    setText( mac );
}