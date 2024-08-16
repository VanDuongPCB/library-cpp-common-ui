#pragma once
#include "FxCommonUIAPI.h"
#include "QLineEdit"


class FX_COMMONUI_API FxMacAddressEdit : public QLineEdit
{
public:
    explicit FxMacAddressEdit( QWidget* parent = nullptr );
    ~FxMacAddressEdit();
    const QString GetMacAddress() const;
    void SetMacAddress(const QString& mac);
private slots:
    void CheckMAC( const QString& text );
private:
    
};

