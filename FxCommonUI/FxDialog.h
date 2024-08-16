#pragma once
#include "FxCommonUIAPI.h"
#include "FxTheme.h"

#include <QDialog>


class FX_COMMONUI_API FxDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FxDialog( QWidget* parent = nullptr );
    ~FxDialog();

protected:
    void UpdateTheme( const FxTheme& theme );

private:
    QObjectList GetChildWidgets();


};
