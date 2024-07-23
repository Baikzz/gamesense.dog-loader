#include "main.h"
#include "settings.h"
#include "images.h"
#include <algorithm>

void ui::Before_Loop()
{
    if (images::CS == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, CS_p, sizeof(CS_p), nullptr, nullptr, &images::CS, 0);
    if (images::BG == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, BG_p, sizeof(BG_p), nullptr, nullptr, &images::BG, 0);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.TTF", 13);
}

void ui::render()
{
    custom::begin("gs pasted", window::start_size);
    {
        auto io = ImGui::GetIO();
        auto d = ImGui::GetWindowDrawList();
        static float time = 0.0f;

        if (tab == 0)
        {
            custom::input("###User", "Username", { (window::start_size.x - 175) / 2, 40 }, 175, username, 20, 0);
            custom::input("###Pass", "Password", { (window::start_size.x - 175) / 2, 75 }, 175, password, 20, ImGuiInputTextFlags_Password);

            if (custom::button("Login", { (window::start_size.x - 175) / 2, 125 }, { 175, 25 })) { tab = 1; }
            if (custom::button("Exit", { (window::start_size.x - 175) / 2, 160 }, { 175, 25 })) { exit(0); }
        }

        if (tab == 1)
        {
            window::start_size = window::size_max;
            time += io.DeltaTime;

            custom::child("Select a game", { 20, 20 }, { 280, 155 });
            {
                if (custom::selectable("Counter-Strike 2", "Updated 06/06/24", { 2,2, }, { 276, 45 }, images::CS, selected == 1)) { selected = 1; }
                if (custom::selectable("ww", "Updated 06/06/24", { 2,50 }, { 276, 45 }, images::CS, selected == 2)) { selected = 2; }
            }
            ImGui::EndChild();

            custom::child("Status", { 20, 190 }, { window::size_max.x - 40, 195});
            /* The log display system its actually very basic, i recommend to do your own log system */

            {
                d->AddRect({ 25, 195 }, { window::size_max.x - 25, 380 }, ImGui::GetColorU32(ImVec4(.0588, 0.0588, 0.0588, 1.0000)), 0, 0, 10.f);
                d->AddRect({ 20, 190 }, { window::size_max.x - 20, 385 }, ImGui::GetColorU32(ImVec4(colors::border_color)), 0, 0, 1.f);
                d->AddRect({ 30, 200 }, { window::size_max.x - 30, 375 }, ImGui::GetColorU32(ImVec4(0.1804, 0.1843, 0.1804, 1.000)), 0, 0, 1.f);
                d->AddText({ 30, 183 }, ImColor(255, 255, 255, 255), "Status");

                const char* messages[] = { "Welcome back!", "Current version is 1.0", "Status: UD", "If you are experiencing any bug contact with the support!", "Select a game and press load" };

                float delay = 1.0f;

                for (int i = 0; i < 5; i++)
                {
                    float appearance_time = delay * i;
                    if (time >= appearance_time)
                    {
                        d->AddText({ 40, 210 + 15.f * i }, ImColor(255, 255, 255, 255), messages[i]);
                    }
                }
            }
            ImGui::EndChild();

            custom::child("Buttons", { 315, 20 }, { 184, 155 });
            {
                d->AddRectFilled({315, 20}, {499, 175}, ImGui::GetColorU32(ImVec4(.0588, 0.0588, 0.0588, 1.0000)), 0, 0);
                d->AddRect({315, 20}, {499, 175}, ImGui::GetColorU32(ImVec4(0.1804, 0.1843, 0.1804, 1.000)), 0, 0, 1.f);
                d->AddText({ 325, 13 }, ImColor(255, 255, 255, 255), "Options");

                if (custom::button("Load", { (184 - 145) / 2, 40 }, { 145, 30 })) { time = 0; tab = 2; }
                if (custom::button("Exit", { (184 - 145) / 2, 80 }, { 145, 30 })) { exit(0); } 
            }
            ImGui::EndChild();
        }

        if (tab == 2)
        {
            window::start_size = { 300, 210 };
            
            time += 0.005;
            static float c = 1.0;

            c = ((int)time % 2 == 0) ? std::clamp(c + (1.f - c) * io.DeltaTime * 5, 0.0f, 1.0f) : std::clamp(c + (0.3f - c) * io.DeltaTime * 3, 0.0f, 1.0f);

            ImVec4 text_color = ImVec4(1.f, 1.f, 1.f, c);

            d->AddText({ (window::start_size.x - ImGui::CalcTextSize("Injecting").x) / 2, 100 }, ImGui::GetColorU32(text_color), "Injecting");

            if (time >= 10.f) { exit(0); }
        }
    }
    ImGui::End();
}