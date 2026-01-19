#include "MainMenuUi.h"

void MainMenuUi::update()
{
}

void MainMenuUi::render()
{
    ImVec2 menu_size = ImGui::GetWindowSize();
    ImVec2 menu_pos = ImGui::GetWindowPos();

    ImGui::Begin("Background", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoBackground);

    ImVec2 panel_size(400, 300);
    ImVec2 panel_pos((menu_size.x - panel_size.x) * 0.5f, (menu_size.y - panel_size.y) * 0.5f);

    ImGui::SetNextWindowPos(panel_pos);
    ImGui::SetNextWindowSize(panel_size);

    ImGui::Begin("Main Menu", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar);

    ImGui::SetCursorPosX((menu_size.x - ImGui::CalcTextSize("MY AWESOME GAME").x) * 0.5f);
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "MY AWESOME GAME");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();

    float button_width = 200.0f;
    float button_height = 40.0f;

    ImGui::SetCursorPosX((menu_size.x - button_width) * 0.5f);

    if (ImGui::Button("Play", ImVec2(button_width, button_height))) {
        EngiApp->setScreen(std::make_shared<GameScreen>());
    }

    ImGui::Spacing();

    ImGui::SetCursorPosX((menu_size.x - button_width) * 0.5f);
    if (ImGui::Button("Settings", ImVec2(button_width, button_height))) {
        LOG(INFO) << "Settings do nothing";
    }

    ImGui::Spacing();

    ImGui::SetCursorPosX((menu_size.x - button_width) * 0.5f);
    if (ImGui::Button("Exit", ImVec2(button_width, button_height))) {
        EngiApp->quit(0);
    }

    ImGui::End(); // Main Menu
    ImGui::End(); // Background
}
