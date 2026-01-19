#include "enginecore/core/graphics/ui/DebugUi.h"

DebugUi::DebugUi()
{
    m_fps_counter.reset();
}

void DebugUi::update()
{
    m_fps_counter.update();

    const auto& camera_view = EngiApp->getEntityRegistry().template view<Camera, Transform>();

    if (EngiApp->window()->events()->pressedOnce(Keycode::F3))
    {
        m_show_debug_window = !m_show_debug_window;
    }

    if (EngiApp->window()->events()->pressedOnce(Keycode::F1))
    {
        EngiApp->window()->events()->toggleLockCursor();
    }
    

    //FIXME: something may went wrong
    for (const auto& camera_entity : camera_view)
    {
        camera = std::make_shared<std::reference_wrapper<Camera>>(camera_view.get<Camera>(camera_entity));
        camera_transform = std::make_shared<std::reference_wrapper<Transform>>(camera_view.get<Transform>(camera_entity));
    }
}

void DebugUi::render()
{
    if (!m_show_debug_window) return;
        
    ImGui::Begin("Debug Window", &m_show_debug_window, 
                ImGuiWindowFlags_AlwaysAutoResize);
    
    if (ImGui::CollapsingHeader("Camera Info", ImGuiTreeNodeFlags_DefaultOpen)) 
    {
        ImGui::Text("Position:");
        ImGui::SameLine(100);
        ImGui::Text("X: %.2f, Y: %.2f, Z: %.2f", 
                    camera_transform->get().m_pos.x, 
                    camera_transform->get().m_pos.y, 
                    camera_transform->get().m_pos.z);
        
        ImGui::Text("Rotation:");
        ImGui::SameLine(100);
        ImGui::Text("Pitch: %.1f, Yaw: %.1f, Roll: %.1f", 
                    camera_transform->get().m_pitch, 
                    camera_transform->get().m_yaw, 
                    camera_transform->get().m_roll);
        
        ImGui::Text("FOV:");
        ImGui::SameLine(100);
        ImGui::SliderFloat("##FOV", &camera->get().m_fov, 30.0f, 120.0f, "%.1f deg");
    }
    
    if (ImGui::CollapsingHeader("Performance", ImGuiTreeNodeFlags_DefaultOpen)) 
    {
        float fps = m_fps_counter.getFPS();
        float frameTime = 1000.0f / (fps > 0 ? fps : 1.0f);
        
        ImGui::Text("FPS:");
        ImGui::SameLine(100);
        ImGui::TextColored(getFPSColor(fps), "%.1f", fps);
        
        ImGui::Text("Frame Time:");
        ImGui::SameLine(100);
        ImGui::TextColored(getFrameTimeColor(frameTime), "%.2f ms", frameTime);

        ImGui::PlotLines("FPS History", m_fps_counter.getHistory().data(), 
                        static_cast<int>(m_fps_counter.getHistory().size()), 
                        0, nullptr, 0.0f, 200.0f, 
                        ImVec2(300, 80));
        
        m_draw_calls = MeshStats::m_draw_calls;
        m_triangles_count = MeshStats::m_triangles_count;
        MeshStats::m_draw_calls = 0;
        MeshStats::m_triangles_count = 0;

        ImGui::Separator();
        ImGui::Text("Render Stats:");
        ImGui::Text("Draw Calls: %d", m_draw_calls);
        ImGui::Text("Meshes: %d", MeshStats::m_meshes_count);
        ImGui::Text("Triangles: %d", m_triangles_count);
        
        if (ImGui::Button("Reset Stats")) 
        {
            m_draw_calls = 0;
            m_triangles_count = 0;
        }
    }
    
    if (ImGui::CollapsingHeader("Visual Settings")) 
    {
        // ImGui::Checkbox("Show Grid", &show_grid);
        // ImGui::SameLine();
        // ImGui::Checkbox("Wireframe Mode", &wireframe_mode);
        
        ImGui::Separator();
        ImGui::Text("Visual Aids:");
        
        static bool show_bounding_boxes = false;
        static bool show_normals = false;
        static bool show_colliders = true;
        
        ImGui::Checkbox("Bounding Boxes", &show_bounding_boxes);
        ImGui::Checkbox("Vertex Normals", &show_normals);
        ImGui::Checkbox("Colliders", &show_colliders);
    }
    
    if (ImGui::CollapsingHeader("Physics (wip)")) 
    {
        // ImGui::SliderFloat("Time Scale", &time_scale, 0.0f, 2.0f, "%.2f");
        // ImGui::SliderFloat("Gravity", &gravity, 0.0f, 20.0f, "%.1f m/s²");
        
        ImGui::Separator();
        static bool enable_physics = true;
        ImGui::Checkbox("Enable Physics", &enable_physics);
        
        if (ImGui::Button("Pause Physics (wip)")) 
        {
            //time_scale = 0.0f;
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset Physics (wip)")) 
        {
            // time_scale = 1.0f;
            // gravity = 9.8f;
        }
    }
    
    if (ImGui::CollapsingHeader("Tools")) {
        if (ImGui::Button("Reset Camera")) 
        {
            camera_transform->get().m_pos = {0.0f, 0.0f, 0.0f};
            //camera_transform->m_rotation = {0.0f, 0.0f, 0.0f};
            camera->get().setFov(60.0f);
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Top View")) 
        {
            camera_transform->get().m_pos = {0.0f, 10.0f, 0.0f};
            //camera_transform->m_rotation = {-90.0f, 0.0f, 0.0f};
        }
        
        static bool captureMode = false;
        static float savedPosition[3] = {0, 0, 0};
        
        ImGui::Separator();
        ImGui::Checkbox("Capture Mode", &captureMode);
        
        if (captureMode && ImGui::Button("Capture Position")) 
        {
            savedPosition[0] = camera_transform->get().m_pos.x;
            savedPosition[1] = camera_transform->get().m_pos.y;
            savedPosition[2] = camera_transform->get().m_pos.z;
        }
        
        if (savedPosition[0] != 0 || savedPosition[1] != 0 || savedPosition[2] != 0) 
        {
            ImGui::Text("Saved: %.2f, %.2f, %.2f", 
                        savedPosition[0], savedPosition[1], savedPosition[2]);
        }
    }
    
    if (ImGui::CollapsingHeader("System Info"))
    {
        ImGui::Text("Platform: Windows/Linux/Mac");
        ImGui::Text("Renderer: OpenGL/DirectX/Vulkan");
        ImGui::Text("GPU: NVIDIA/AMD/Intel");
        
        static float memory_usage = 0.65f;
        ImGui::Text("Memory Usage:");
        ImGui::SameLine(150);
        ImGui::ProgressBar(memory_usage, ImVec2(150, 20));
    }
    
    ImGui::Separator();
    ImGui::Text("Debug Controls:");
    
    if (ImGui::Button("Hide/Show")) 
    {
        m_show_debug_window = !m_show_debug_window;
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Minimize All (in wip)")) 
    {
        
    }
    
    ImGui::SameLine();
    ImGui::Text("| Press F3 to toggle");
    
    ImGui::End();
}

ImVec4 DebugUi::getFPSColor(const float &fps)
{
    if (fps >= 60.0f) 
        return ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
    if (fps >= 30.0f) 
        return ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // yellow
    return ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // red
}

ImVec4 DebugUi::getFrameTimeColor(const float &frameTime)
{
    if (frameTime <= 16.67f) 
        return ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // 60+ FPS
    if (frameTime <= 33.33f) 
        return ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // 30-60 FPS
    return ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // <30 FPS
}
