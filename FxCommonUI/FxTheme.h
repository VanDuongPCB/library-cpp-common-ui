#pragma once
#include "FxCommonUIAPI.h"

#include <QString>
#include <QMap>
#include <QColor>
#include <QPalette>
#include <QIcon>

class FX_COMMONUI_API FxTheme
{
public:
	FxTheme( );
	FxTheme( const QString& path, bool bLoadData = true );
	~FxTheme();
	const QString GetName() const;
	const QIcon GetIcon() const;
	const QString GetStyleSheet() const;
	const QString GetStyleSheet( const QString& className ) const;
	const QString GetStyleSheet( const QString& className, const QString& objectName ) const;
	const QString GetCustomStyleSheet( const QString& objectInfo ) const;
	bool Load();
private:
	QString m_path;
	QString m_name;
	QIcon m_Icon;
	QMap<QString, QString> m_classCss;
	QMap<QString, QString> m_objectCss;
	QMap<int, QColor> m_paletteColors;

	void ReadInfos( const QString& path );
	void ReadClassCss( const QString& path );
	void ReadCustomStyleSheet( const QString& path );
	void ReadPalette( const QString& path );
};