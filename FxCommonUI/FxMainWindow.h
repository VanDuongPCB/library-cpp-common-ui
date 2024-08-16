#pragma once
#include "FxCommonUIAPI.h"
#include "FxTheme.h"

#include <QMainWindow>


class FX_COMMONUI_API FxMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FxMainWindow( QWidget* parent = nullptr );
    ~FxMainWindow();

protected:
    void UpdateTheme( const FxTheme& theme );

private:
    QObjectList GetChildWidgets();
    

};
