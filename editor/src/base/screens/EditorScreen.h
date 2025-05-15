#pragma once
#ifndef SCREENS_EDITORSCREEN_H_
#define SCREENS_EDITORSCREEN_H_

#include <enginecore/utils/ImguiIncludes.h>

#include <enginecore/core/screens/Screen.h>

#include <enginecore/core/EngineCoreApplication.h>

class EditorScreen : public Screen
{
private:
	struct SceneObject 
	{
		std::string name;
		glm::vec3 position = { 0,0,0 };
		glm::vec3 rotation = { 0,0,0 };
		glm::vec3 scale = { 1,1,1 };
		glm::vec3 color = { 1,1,1 };
		float metallic = 0.0f;
		float roughness = 0.5f;
	};

public:
	EditorScreen();
	~EditorScreen() = default;

public:
	void update(const float& delta) override;
	void draw(const float& delta) override;

	void updateGui();

private:
	bool m_show_scene_view = true;
	bool m_show_hierarchy = true;
	bool m_show_inspector = true;
	bool m_show_assets = false;
	bool m_show_console = false;
	bool m_show_about = false;

	bool m_show_grid = true;
	bool m_show_gizmos = true;

	std::vector<SceneObject> sceneObjects;
	SceneObject* m_selected_object = nullptr;
};


#endif // !SCREENS_EDITORSCREEN_H_