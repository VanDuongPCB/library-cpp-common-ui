#include "FxMainWindow.h"
#include "FxThemeServices.h"
#include <QCoreApplication>
#include <QApplication>
#include <QEvent>

FxMainWindow::FxMainWindow( QWidget* parent ) : QMainWindow( parent )
{
    UpdateTheme( GetThemeServices()->Data() );
    connect( GetThemeServices(), &FxThemeServices::ThemeChanged, this, &FxMainWindow::UpdateTheme );
}

FxMainWindow::~FxMainWindow()
{
}

void FxMainWindow::UpdateTheme( const FxTheme& theme )
{
    setStyleSheet( theme.GetStyleSheet() );
    QWidget* root = centralWidget();
    if ( !root )
        return;

    QString className = metaObject()->className();
    QObjectList childs = GetChildWidgets();
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

QObjectList FxMainWindow::GetChildWidgets()
{

    QObjectList childs;
    QWidget* root = centralWidget();
    if ( !root )
        return childs;

    childs = root->children();
    for ( int i = 0; i < childs.size(); i++ )
    {
        if (! childs[ i ]->isWidgetType() )
            continue;
        QObjectList childs2 = childs[ i ]->children();
        for ( auto child : childs2 )
        {
            if ( !child->isWidgetType() )
                continue;

            QString name = child->objectName();
            if ( name.isEmpty() || name.startsWith( "qt_" ) )
                continue;
            childs.push_back( child );
        }

    }

    return childs;
}
