#pragma once
#include "FxCommonUIAPI.h"
#include <QPushButton>


class FX_COMMONUI_API FxRounedButton : public QPushButton
{
    Q_OBJECT
public:
    explicit FxRounedButton( QWidget* parent = nullptr );
    ~FxRounedButton();

private:
    void showEvent( QShowEvent* event );
    void resizeEvent( QResizeEvent* event );
    void Rouned();
};

