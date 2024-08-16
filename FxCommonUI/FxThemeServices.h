#pragma once
#include "FxCommonUIAPI.h"
#include "FxTheme.h"

#include <QObject>

class FX_COMMONUI_API FxThemeServices : public QObject
{
	Q_OBJECT
public:
	FxThemeServices( QObject* parent = nullptr );
	~FxThemeServices();
	QMap<int, FxTheme> Availableds();
	bool SetTheme(const QString& themeName);
	bool Install( const QString& path );
	void ReLoad();
	FxTheme Data();
	QWidget* GetControlWidget();

signals:
	void ThemeChanged( const FxTheme& theme );

private slots:
	void OnNextTheme();

private:
	FxTheme m_themeData;
	QWidget* m_controlWidget;
};

FxThemeServices FX_COMMONUI_API *GetThemeServices();