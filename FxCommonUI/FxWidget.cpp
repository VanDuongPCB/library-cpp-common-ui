#include "FxWidget.h"
#include "FxThemeServices.h"

FxWidget::FxWidget( QWidget* parent ) :QWidget( parent )
{
}

FxWidget::~FxWidget()
{
}

QObjectList FxWidget::GetChildWidgets()
{

    QObjectList childs = children();
    for ( int i = 0; i < childs.size(); i++ )
    {
        if ( !childs[ i ]->isWidgetType() )
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

void FxWidget::UpdateTheme()
{
    FxTheme themeData = GetThemeServices()->Data();

    qDebug() << "==================================";
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
                widget->setStyleSheet( themeData.GetCustomStyleSheet( widgetId ) );
        }
        catch ( ... )
        {

        }

        qDebug() << "Child name = " << widgetId;
    }


    qDebug() << "==================================";
}