#pragma once
#include "FxCommonUIAPI.h"
#include "QLineEdit"


class FX_COMMONUI_API MACAddressEdit : public QLineEdit
{
public:
    explicit MACAddressEdit( QWidget* parent = nullptr );
    ~MACAddressEdit();

private:

};

