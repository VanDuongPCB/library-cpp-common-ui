#pragma once
#include "FxCommonUIAPI.h"
#include "FxWidget.h"
#include "FxTheme.h"

class FX_COMMONUI_API FxAnchorBox : public FxWidget
{
public:
    explicit FxAnchorBox( QWidget* parent = nullptr );
    ~FxAnchorBox();
protected:
    bool eventFilter( QObject* object, QEvent* event ) override;

public:
    void SetAnchor( int left, int top, int right, int bottom );
    void AddWidget( QWidget* widget );
    void UpdatePosition();

private slots:
    void UpdateTheme( const FxTheme& theme );

private:
    int m_left;
    int m_top;
    int m_right;
    int m_bottom;
    QList<QWidget*> m_widgets;

    
};