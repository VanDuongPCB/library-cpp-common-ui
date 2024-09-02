#include "FxTheme.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

FxTheme::FxTheme()
{
}

FxTheme::FxTheme( const QString& path, bool bLoadData ) : FxTheme()
{
    m_path = path;
    ReadInfos( path );

    if ( !bLoadData )
        return;

    Load();
}

FxTheme::~FxTheme()
{
}

const QString FxTheme::GetName() const
{
    return m_name;
}

const QIcon FxTheme::GetIcon() const
{
    return m_Icon;
}

const QString FxTheme::GetStyleSheet() const
{
    QStringList css;
    QStringList classNames = m_classCss.keys();
    for ( auto &className : classNames )
    {
        if ( className.startsWith( "#" ) )
            continue;
        css.push_back( m_classCss[ className ] );
    }
    for ( auto &className : classNames )
    {
        if ( !className.startsWith( "#" ) )
            continue;
        css.push_back( m_classCss[ className ] );
    }


    return css.join( "\n" );
}

const QString FxTheme::GetStyleSheet( const QString& className ) const
{
    return "";
}

const QString FxTheme::GetStyleSheet( const QString& className, const QString& objectName ) const
{
    return "";
}

const QString FxTheme::GetCustomStyleSheet( const QString& objectInfo ) const
{
    return m_objectCss[ objectInfo ];
}

bool FxTheme::Load()
{
    ReadClassCss( m_path );
    ReadCustomStyleSheet( m_path );
    ReadPalette( m_path );
    return true;
}

void FxTheme::ReadInfos( const QString& path )
{
    QFileInfo fi( path );
    m_name = fi.baseName();
}

void FxTheme::ReadClassCss( const QString& path )
{
    QString dirPath = path + "/classes.css";
    QFileInfoList fileInfoList = QDir( dirPath ).entryInfoList( { "*.css" } );
    for ( QFileInfo fileInfo : fileInfoList )
    {
        QFile styleReader( fileInfo.absoluteFilePath() );
        if ( !styleReader.open( QIODevice::ReadOnly ) )
            continue;
        QString css = styleReader.readAll();
        styleReader.close();
        QString className = fileInfo.baseName();
        m_classCss[ className ] = css;
    }

}

void FxTheme::ReadCustomStyleSheet( const QString& path )
{
    QFileInfoList fileList = QDir( path ).entryInfoList( { "*.css" } );
    for ( auto &fileInfo : fileList )
    {
        QFile cssReader( fileInfo.absoluteFilePath() );
        if ( !cssReader.open( QIODevice::ReadOnly ) )
            continue;
        QString css = cssReader.readAll();
        cssReader.close();
        QString fileName = fileInfo.baseName();
        m_objectCss[ fileName ] = css;
    }
}

void FxTheme::ReadPalette( const QString& path )
{
    ////palette.setColor( , QColor( 48, 48, 48 ) );
    ////palette.setColor( QPalette::Disabled, QPalette::Text, QColor( 127, 127, 127 ) );
    ////palette.setColor( QPalette::Light, QColor( 35, 35, 35 ) );
    ////palette.setColor( QPalette::Midlight, QColor( 35, 35, 35 ) );
    ////palette.setColor( QPalette::Mid, QColor( 35, 35, 35 ) );
    ////palette.setColor( QPalette::Dark, QColor( 35, 35, 35 ) );
    ////palette.setColor( QPalette::Shadow, QColor( 127, 127, 127 ) );
    ////palette.setColor( QPalette::Button, QColor( 255, 255, 255 ) );
    ////palette.setColor( QPalette::ButtonText, QColor( 48, 48, 48 ) );
    ////palette.setColor( QPalette::Disabled, QPalette::ButtonText, QColor( 127, 127, 127 ) );
    ////palette.setColor( QPalette::BrightText, Qt::red );
    ////palette.setColor( QPalette::Link, QColor( 42, 130, 218 ) );
    ////palette.setColor( QPalette::Highlight, QColor( 42, 130, 218 ) );
    ////palette.setColor( QPalette::Disabled, QPalette::Highlight, QColor( 80, 80, 80 ) );
    ////palette.setColor( QPalette::HighlightedText, Qt::white );
    ////palette.setColor( QPalette::Disabled, QPalette::HighlightedText, QColor( 127, 127, 127 ) );
    //static const QMap<QString, QPalette::ColorRole> colorRoleMap{
    //    {"Window",QPalette::Window},
    //    {"WindowText",QPalette::WindowText},
    //    {"Disabled",QPalette::Disabled},
    //    {"xxxxxxx",QPalette::Base},
    //    {"xxxxxxx",QPalette::AlternateBase},
    //    {"xxxxxxx", QPalette::ToolTipBase},
    //    {"xxxxxxx",QPalette::ToolTipText},
    //    {"xxxxxxx",QPalette::Text},
    //    {"xxxxxxx",xxxxxxxxxxxx},
    //    {"xxxxxxx",xxxxxxxxxxxx},

    //    {"xxxxxxx",xxxxxxxxxxxx},
    //            {"xxxxxxx",xxxxxxxxxxxx},
    //    {"xxxxxxx",xxxxxxxxxxxx},
    //    {"xxxxxxx",xxxxxxxxxxxx},

    //    {"xxxxxxx",xxxxxxxxxxxx},
    //            {"xxxxxxx",xxxxxxxxxxxx},
    //    {"xxxxxxx",xxxxxxxxxxxx},
    //    {"xxxxxxx",xxxxxxxxxxxx},

    //    {"xxxxxxx",xxxxxxxxxxxx},
    //            {"xxxxxxx",xxxxxxxxxxxx},
    //    {"xxxxxxx",xxxxxxxxxxxx},
    //    {"xxxxxxx",xxxxxxxxxxxx},

    //    {"xxxxxxx",xxxxxxxxxxxx},
    //};
}