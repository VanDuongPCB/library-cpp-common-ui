#include "FxThemeServices.h"
#include "FxRounedButton.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


FxThemeServices::FxThemeServices( QObject* parent ) : QObject( parent ),
m_controlWidget( nullptr )
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString themeDir = appPath + "/themes";
    QDir().mkdir( themeDir );
}

FxThemeServices::~FxThemeServices()
{
}

QMap<int, FxTheme> FxThemeServices::Availableds()
{
    QMap<int, FxTheme> themes;
    QString appPath = QCoreApplication::applicationDirPath();
    QString themeDir = appPath + "/themes";
    QFileInfoList dirList = QDir( themeDir ).entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot );
    int index = 0;
    for ( auto &dirInfo : dirList )
    {
        FxTheme theme( dirInfo.absoluteFilePath(), false );
        themes[ index++ ] = theme;
    }
    return themes;
}

bool FxThemeServices::SetTheme( const QString& themeName )
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString configPath = appPath + "/themes/settings.json";
    QJsonObject obj;
    obj.insert( "select", themeName );
    QJsonDocument doc;
    doc.setObject( obj );
    QFile jsonWriter( configPath );
    if ( jsonWriter.open( QIODevice::WriteOnly ) )
    {
        jsonWriter.write( doc.toJson() );
        jsonWriter.close();
        ReLoad();
    }

    return true;
}

bool FxThemeServices::Install( const QString& path )
{
    return false;
}

void FxThemeServices::ReLoad()
{
    QString appPath = QCoreApplication::applicationDirPath();
    QString configPath = appPath + "/themes/settings.json";
    QFile jsonReader( configPath );
    if ( !jsonReader.open( QIODevice::ReadOnly ) )
    {
        return;
    }

    QByteArray json = jsonReader.readAll();
    jsonReader.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson( json );
    QJsonObject jsonObj = jsonDoc.object();
    QString currentTheme = jsonObj.value( "select" ).toString();

    QString themeDir = appPath + "/themes/" + currentTheme;
    m_themeData = FxTheme( themeDir );

    emit ThemeChanged( m_themeData );
}

FxTheme FxThemeServices::Data()
{
    return m_themeData;
}

QWidget* FxThemeServices::GetControlWidget()
{
    FxRounedButton* button = static_cast< FxRounedButton* >( m_controlWidget );
    if ( !button )
    {
        button = new FxRounedButton();
        button->setGeometry( 0, 0, 25, 25 );
        connect( button, &FxRounedButton::clicked, this, &FxThemeServices::OnNextTheme );
        m_controlWidget = button;
    }
        
    button->setText( m_themeData.GetName() );
    return m_controlWidget;
}

void FxThemeServices::OnNextTheme()
{
    QMap<int, FxTheme> themes = Availableds();
    if ( themes.size() < 1 )
        return;

    for ( auto it = themes.begin(); it != themes.end(); it++ )
    {
        if ( it.value().GetName() == m_themeData.GetName() )
        {
            int nextIndex = it.key() + 1;
            if ( !themes.contains( nextIndex ) )
                nextIndex = 0;
            SetTheme( themes[ nextIndex ].GetName() );
            GetControlWidget();
            break;
        }
    }
}

FxThemeServices* GetThemeServices()
{
    static FxThemeServices instance;
    return &instance;
}