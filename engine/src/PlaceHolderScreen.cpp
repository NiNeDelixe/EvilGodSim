#include "enginecore/core/screens/PlaceHolderScreen.h"

void PlaceHolderScreen::update(const float& delta)
{
    ImGui::SetNextWindowSize({ static_cast<float>(EngiApp->window()->viewports()[0]->getWidth()),
            static_cast<float>(EngiApp->window()->viewports()[0]->getHeight())});
    
    ImGui::Begin("Fullscreen Window", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground);

    ImGui::Text("Place Holder Screen");
    
    ImGui::End();
}

void PlaceHolderScreen::draw(const float& delta)
{
}
