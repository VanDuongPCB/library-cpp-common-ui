#pragma once
#include "FxCommonUIAPI.h"
#include <QWidget>

class FX_COMMONUI_API FxWidget : public QWidget
{
public:
	explicit FxWidget(QWidget *parent = nullptr);
	~FxWidget();
protected:
	void UpdateTheme();
private:
	QObjectList GetChildWidgets();
};

