#pragma once

#ifdef FxCommonUI_EXPORTS
#define FX_COMMONUI_API __declspec(dllexport)
#else
#define FX_COMMONUI_API __declspec(dllimport)
#endif // FxCommonUI_EXPORTS
