#pragma once
#include "main.h"

inline ID3D11Device* g_pd3dDevice = nullptr;
inline ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
inline IDXGISwapChain* g_pSwapChain = nullptr;
inline UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
inline ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

const wchar_t project_name[] = L"gs pasted";

inline int tab;
inline int selected;

inline char username[20] = "";
inline char password[20] = "";

inline bool done = false;