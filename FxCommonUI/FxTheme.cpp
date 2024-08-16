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

}