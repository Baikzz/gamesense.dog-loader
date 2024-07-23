#pragma once

#include <d3d11.h>
#include <windows.h>
#include <dwmapi.h>
#include <string>
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

inline HWND hwnd;
inline RECT rc;

namespace window {
	inline ImVec2 start_size = ImVec2(300.f, 210.f);
	inline ImVec2 size_max = ImVec2(520.f, 400.f);
}

namespace images {
	inline ID3D11ShaderResourceView* CS = nullptr;
	inline ID3D11ShaderResourceView* BG = nullptr;
}

namespace custom {
	void begin(const char* name, ImVec2 size);
	void child(const char* name, ImVec2 pos, ImVec2 size);
	bool input(const char* label, const char* hint, ImVec2 pos, float SizeX, char buf[], size_t bufsize, ImGuiInputTextFlags flags);
	bool button(const char* label, ImVec2 pos, ImVec2 size);
	bool selectable(const char* label, const char* bio, ImVec2 pos, ImVec2 size, ID3D11ShaderResourceView* pic, bool active);
}

namespace colors 
/* No easy color items support since it's a paste, if you want to modify the item colors, you have to modify each item */

{
	inline ImVec4 border_color = { 0.1529, 0.1529, 0.1490, 1.0000 };
	inline ImVec4 bg = { 0.0706, 0.0745, 0.0706, 1.f };
}

namespace ui {
	void render();
	void Before_Loop();
}