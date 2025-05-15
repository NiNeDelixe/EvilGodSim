#include "EditorScreen.h"

EditorScreen::EditorScreen()
{
	//float vertices1[] = {
	//	// (x, y, z)   UV (s, t)
	//	-0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
	//	 0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
	//	-0.5f,  0.5f, 0.0f,    0.0f, 1.0f
	//};

	//unsigned int indices1[] = {
	//0, 1, 2,
	//0, 2, 3
	//};
	//EngiApp->m_meshes.push_back(std::make_shared<Mesh<>>(vertices1, 12, indices1, 6));
}

void EditorScreen::update(const float& delta)
{
	updateGui();

	const auto& main_shader = EngiApp->assets().lock()->get<GLShader>("main");

	main_shader->use();
}


void EditorScreen::draw(const float& delta)
{
}

void EditorScreen::updateGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize({ static_cast<float>(EngiApp->window()->viewports()[0]->getWidth()),
			static_cast<float>(EngiApp->window()->viewports()[0]->getHeight()) });

	ImGui::Begin("Editor Gui", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene")) { /* ... */ }
            if (ImGui::MenuItem("Open...", "Ctrl+O")) { /* ... */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* ... */ }
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { /* ... */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) { EngiApp->quit(0); }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* ... */ }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* ... */ }
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "Ctrl+X")) { /* ... */ }
            if (ImGui::MenuItem("Copy", "Ctrl+C")) { /* ... */ }
            if (ImGui::MenuItem("Paste", "Ctrl+V")) { /* ... */ }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Scene View", nullptr, &m_show_scene_view);
            ImGui::MenuItem("Hierarchy", nullptr, &m_show_hierarchy);
            ImGui::MenuItem("Inspector", nullptr, &m_show_inspector);
            ImGui::MenuItem("Assets", nullptr, &m_show_assets);
            ImGui::MenuItem("Console", nullptr, &m_show_console);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Game"))
        {
            if (ImGui::MenuItem("Play", "Ctrl+P")) { /* ... */ }
            if (ImGui::MenuItem("Pause", "Ctrl+Shift+P")) { /* ... */ }
            if (ImGui::MenuItem("Step", "Ctrl+Alt+P")) { /* ... */ }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools"))
        {
            /*if (ImGui::MenuItem("ImPlot Demo")) { show_implot_demo = !show_implot_demo; }*/
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About")) { m_show_about = true; }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // editor
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    // scene win
    if (m_show_scene_view)
    {
        ImGui::Begin("Scene View", &m_show_scene_view);

        // render scene
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        //ImGui::Image((void*)(intptr_t)sceneTexture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

        // Scene tools
        if (ImGui::BeginChild("Scene Tools", ImVec2(0, 30), true))
        {
            ImGui::Checkbox("Show Grid", &m_show_grid);
            ImGui::SameLine();
            ImGui::Checkbox("Show Gizmos", &m_show_gizmos);
            ImGui::SameLine();
            ImGui::Text("View: ");
            ImGui::SameLine();
            //if (ImGui::Button("Perspective")) { camera.SetPerspective(); }
            ImGui::SameLine();
            //if (ImGui::Button("Orthographic")) { camera.SetOrthographic(); }
        }
        ImGui::EndChild();

        ImGui::End();
    }

    // Ierachy
    if (m_show_hierarchy)
    {
        ImGui::Begin("Hierarchy", &m_show_hierarchy);

        if (ImGui::TreeNode("Scene"))
        {
            // Ierachy ex
            if (ImGui::TreeNode("Main Camera"))
            {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Directional Light"))
            {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Environment"))
            {
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Objects"))
            {
                for (auto& obj : sceneObjects)
                {
                    ImGui::Selectable(obj.name.c_str(), m_selected_object == &obj);
                    if (ImGui::IsItemClicked())
                    {
                        m_selected_object = &obj;
                    }
                }
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        ImGui::End();
    }

    // Inspector
    if (m_show_inspector)
    {
        ImGui::Begin("Inspector", &m_show_inspector);

        if (!m_selected_object)
        {
            ImGui::End();
        }
        else
        {
            ImGui::Text("Name: %s", m_selected_object->name.c_str());
            ImGui::Separator();

            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::DragFloat3("Position", &m_selected_object->position.x, 0.1f);
                ImGui::DragFloat3("Rotation", &m_selected_object->rotation.x, 1.0f);
                ImGui::DragFloat3("Scale", &m_selected_object->scale.x, 0.1f);
            }

            if (ImGui::CollapsingHeader("Mesh Renderer"))
            {
                ImGui::ColorEdit3("Color", &m_selected_object->color.x);
                ImGui::DragFloat("Metallic", &m_selected_object->metallic, 0.01f, 0.0f, 1.0f);
                ImGui::DragFloat("Roughness", &m_selected_object->roughness, 0.01f, 0.0f, 1.0f);
            }

            ImGui::End();
        }
    }

    //Status bar
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
    if (ImGui::BeginViewportSideBar("##StatusBar", ImGui::GetMainViewport(), ImGuiDir_Down, ImGui::GetFrameHeight(), window_flags))
    {
        if (ImGui::BeginMenuBar()) 
        {
            ImGui::Text("Ready");
            ImGui::SameLine();
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::SameLine(ImGui::GetWindowWidth() - 100);
            ImGui::Text("%.1f/%.1f", /*camera.GetPosition().x*/0, /*camera.GetPosition().y*/0);
            ImGui::EndMenuBar();
        }
        ImGui::End();
    }

    // Style
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

	ImGui::End();
}
