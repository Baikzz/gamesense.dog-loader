#include "main.h"

DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground;
void style();
void mw();

void custom::begin(const char* name, ImVec2 size)
/* A way to do our window's background, i prefer this way drawing a rectangle that fills up the window 
   instead of changing the window backgrounds color */

{
	ImGui::Begin(name, NULL, window_flags);
	ImGui::SetWindowSize(size);

    auto d = ImGui::GetWindowDrawList();

	d->AddRectFilled({ 0,0 }, size, ImGui::GetColorU32(colors::bg));
    //d->AddImage(images::BG, { -40,-40 }, {size.x + 50, size.y + 80}); //tried to add their chess table background with an image, but didnt work at all

    d->AddRectFilledMultiColor({ 5,5 }, { window::start_size.x - 5, 7 }, ImColor(255, 0, 0, 255), ImColor(0, 255, 0, 255), ImColor(0, 0, 255, 255), ImColor(255, 255, 0, 255));
    d->AddRect({ 0,0 }, window::start_size, ImGui::GetColorU32(colors::border_color), 0, 0, 7.f);
    d->AddRect({ 0,0 }, window::start_size, ImColor(0, 0, 0, 255));

    style();
    mw();
}

void custom::child(const char* name, ImVec2 pos, ImVec2 size)
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, colors::border_color);

    ImGui::SetNextWindowPos(pos);
    ImGui::BeginChild(name, size);
}

void style()
/* Setting up a custom style vars */

{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowBorderSize = 0.f;
    style.FrameBorderSize = 0.f;
    style.FrameRounding = 2.f;
    style.WindowPadding = ImVec2(0, 0);
    style.ScrollbarSize = 5.f;
}

void mw()
/* This makes the window moving */

{
    GetWindowRect(hwnd, &rc);
    MoveWindow(hwnd, rc.left + ImGui::GetWindowPos().x, rc.top + ImGui::GetWindowPos().y, window::size_max.x, window::size_max.y, TRUE);
    ImGui::SetWindowPos(ImVec2(0.f, 0.f));
}

//custom items

bool custom::input(const char* label, const char* hint, ImVec2 pos, float SizeX, char buf[], size_t bufsize, ImGuiInputTextFlags flags)
/* A very basic input, change the colors of the item, also adds a border */

{
    auto d = ImGui::GetWindowDrawList();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.1333, 0.1373, 0.1373, 1.0000 });
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5,6 });

    ImGui::SetCursorPos(pos);
    ImGui::SetNextItemWidth(SizeX);
    bool result = ImGui::InputTextWithHint(label, hint, buf, bufsize, flags);

    ImVec2 MIN = ImGui::GetItemRectMin();
    ImVec2 MAX = ImGui::GetItemRectMax();

    d->AddRect(MIN, MAX, ImGui::GetColorU32(colors::border_color), 0, 0, 2.f);
    d->AddLine({ MIN.x - 1, MAX.y + 2}, { MAX.x + 1, MAX.y + 2}, ImColor(0, 0, 0, 255));

    ImGui::PopStyleVar(2);
    return result;
}

bool custom::button(const char* label, ImVec2 pos, ImVec2 size)
/* A very basic button, it just changes the colors and ad a border */

{
    auto d = ImGui::GetWindowDrawList();
    ImGui::PushStyleColor(ImGuiCol_Button, { 0.1333, 0.1373, 0.1373, 1.0000 });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.1333, 0.1373, 0.1373, 0.9});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1333, 0.1373, 0.1373, 1});

    ImGui::SetCursorPos(pos);
    bool result = ImGui::Button(label, size);

    ImVec2 MIN = ImGui::GetItemRectMin();
    ImVec2 MAX = ImGui::GetItemRectMax();

    d->AddRect(MIN, MAX, ImGui::GetColorU32(colors::border_color), 0, 0, 2.f);
    d->AddLine({ MIN.x - 1, MAX.y + 2 }, { MAX.x + 1, MAX.y + 2 }, ImColor(0, 0, 0, 255));

    ImGui::PopStyleColor(3);
    return result;
}

bool custom::selectable(const char* label, const char* bio, ImVec2 pos, ImVec2 size, ID3D11ShaderResourceView* pic, bool active)
/* A very basic custom selectable */

{
    auto d = ImGui::GetWindowDrawList();

    ImGui::SetCursorPos(pos);
    bool result = ImGui::InvisibleButton(label, size);

    ImVec2 MIN = ImGui::GetItemRectMin();
    ImVec2 MAX = ImGui::GetItemRectMax();

    ImVec4 Fill_Color = active ? ImVec4(0.1333, 0.1373, 0.1373, 1.0000) : ImVec4(0.1333, 0.1373, 0.1373, .2);

    d->AddRectFilled(MIN, MAX, ImGui::GetColorU32(Fill_Color));
    d->AddRect(MIN, MAX, ImGui::GetColorU32(ImVec4(0.1804, 0.1843, 0.1804, 1.000)));

    d->AddImage(pic, { MIN.x + 5, MIN.y + 5 }, { MIN.x + 40, MIN.y + 40 });

    d->AddText({ MIN.x + 70, MIN.y + 7 }, ImColor(0, 255, 0, 255), label);
    d->AddText({ MIN.x + 70, MIN.y + 22 }, ImColor(255, 255, 255, 255), bio);

    return result;
}