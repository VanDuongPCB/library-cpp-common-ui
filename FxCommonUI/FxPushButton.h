#pragma once
#include "FxCommonUIAPI.h"
#include <QPushButton>

class FX_COMMONUI_API FxPushButton : public QPushButton
{
	Q_OBJECT
public:
	explicit FxPushButton(QWidget *parent = nullptr);
	~FxPushButton();

private:

};

