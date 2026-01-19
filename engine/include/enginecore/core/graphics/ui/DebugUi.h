#pragma once
#ifndef UI_DEBUGUI_H_
#define UI_DEBUGUI_H_

#include "enginecore/core/CoreDefines.h"

#include <chrono>
#include <cmath>
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "enginecore/core/EngineCoreApplication.h"

#include "enginecore/core/graphics/render/Mesh.h"
#include "enginecore/core/ecs/entities/Camera.h"
#include "enginecore/core/ecs/components/Transform.h"
#include "enginecore/core/window/Input.h"

#include "enginecore/core/graphics/ui/Ui.h"

#include "enginecore/utils/FPSStats.h"

class DebugUi : public Ui
{
public:
    DebugUi();
    ~DebugUi() = default;

public:
    virtual void update() override;
    virtual void render() override;

private:
    ImVec4 getFPSColor(const float& fps);
    ImVec4 getFrameTimeColor(const float& frameTime);

private:
    bool m_show_debug_window = false;

    std::vector<float> m_fps_history;
    const int m_max_history_size = 100;

    size_t m_draw_calls = 0;
    size_t m_triangles_count = 0;

    FPSCounter m_fps_counter = FPSCounter();

    std::shared_ptr<std::reference_wrapper<Camera>> camera = nullptr;
    std::shared_ptr<std::reference_wrapper<Transform>> camera_transform = nullptr;
};

#endif  // UI_DEBUGUI_H_
