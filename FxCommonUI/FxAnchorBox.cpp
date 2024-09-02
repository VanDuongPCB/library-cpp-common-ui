#include "FxAnchorBox.h"
#include "FxThemeServices.h"
#include <QEvent>

FxAnchorBox::FxAnchorBox( QWidget* parent ) : FxWidget( parent ),
m_left( 0 ),
m_top( 0 ),
m_right( -1 ),
m_bottom( -1 )
{
    UpdateTheme( GetThemeServices()->Data() );
    connect( GetThemeServices(), &FxThemeServices::ThemeChanged, this, &FxAnchorBox::UpdateTheme );
    if ( parent )
        parent->installEventFilter( this );

    UpdatePosition();
   
}

FxAnchorBox::~FxAnchorBox()
{
}

bool FxAnchorBox::eventFilter( QObject* object, QEvent* event )
{
    if ( object != parent() )
        return false;

    if ( event->type() == QEvent::Resize )
    {
        UpdatePosition();
    }


    return false;
}

void FxAnchorBox::UpdateTheme( const FxTheme& theme )
{
    setStyleSheet( theme.GetStyleSheet() );
    QString className = metaObject()->className();
    QObjectList childs = children();
    for ( auto child : childs )
    {
        if ( !child->isWidgetType() )
            continue;

        QString widgetId = className + "#" + child->objectName();
        try
        {
            QWidget* widget = static_cast< QWidget* >( child );
            if ( widget )
                widget->setStyleSheet( theme.GetCustomStyleSheet( widgetId ) );
        }
        catch ( ... )
        {

        }
    }
}

void FxAnchorBox::SetAnchor( int left, int top, int right, int bottom )
{
    m_left = left;
    m_top = top;
    m_right = right;
    m_bottom = bottom;
    UpdatePosition();
}

void FxAnchorBox::AddWidget( QWidget* widget )
{
    if ( !widget )
        return;
    

    for ( auto it : m_widgets )
    {
        if ( it == widget )
            return;
    }

    m_widgets.push_back( widget );

    int x = 0;
    int y = 0;
    int padding = 10;
    int newWidth = 0;
    int newHeight = 0;
    for ( auto widget : m_widgets )
    {
        QSize wsize = widget->size();
        widget->setParent( this );
        widget->setGeometry( x, y, wsize.width(), wsize.height() );
        x += wsize.width() + padding;
        

        if ( wsize.height() > newHeight )
            newHeight = wsize.height();

        newWidth += wsize.width();
        newWidth += padding;
    }

    newWidth -= padding;

    QRect geo = geometry();
    geo.setSize( QSize( newWidth, newHeight ) );
    setGeometry( geo );
    UpdatePosition();
}


void FxAnchorBox::UpdatePosition()
{
    if ( !parentWidget() )
        return;

    QRect currentGeometry = geometry();
    QRect newGeometry = currentGeometry;
    QSize parentSize = parentWidget()->size();

    if ( m_left >= 0 && m_right >= 0 )
    {
        newGeometry.setX( m_left );
        newGeometry.setWidth( parentSize.width() - m_right - m_left );
    }
    else if ( m_left >= 0 )
    {
        newGeometry.setX( m_left );
        newGeometry.setWidth( currentGeometry.width() );
    }
    else if ( m_right >= 0 )
    {
        newGeometry.setX( parentSize.width() - currentGeometry.width() - m_right );
        newGeometry.setWidth( currentGeometry.width() );
    }

    if ( m_top >= 0 && m_bottom >= 0 )
    {
        newGeometry.setY( m_top );
        newGeometry.setHeight( parentSize.height() - m_top - m_bottom );
    }
    else if ( m_top >= 0 )
    {
        newGeometry.setY( m_top );
        newGeometry.setHeight( currentGeometry.height() );
    }
    else if ( m_bottom > 0 )
    {
        newGeometry.setY( parentSize.height() - m_bottom - currentGeometry.height() );
        newGeometry.setHeight( currentGeometry.height() );
    }

    setGeometry( newGeometry );
}