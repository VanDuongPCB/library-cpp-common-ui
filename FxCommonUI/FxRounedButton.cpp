#include "FxRounedButton.h"
FxRounedButton::FxRounedButton( QWidget* parent ) : QPushButton( parent )
{
    Rouned();
}

FxRounedButton::~FxRounedButton()
{
}

void FxRounedButton::showEvent( QShowEvent* event )
{
    Rouned();
}

void FxRounedButton::resizeEvent( QResizeEvent* event )
{
    Rouned();
}

void FxRounedButton::Rouned()
{
    int size = std::min( width(), height() );
    int radius = size / 2;
    QString css = QString( "border-radius:%1px" ).arg( radius );
    //setStyleSheet( css );
}