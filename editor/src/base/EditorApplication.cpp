#include "EditorApplication.h"

EditorApplication::EditorApplication(int argc, char** argv)
	: EngineCoreApplication(argc, argv)
{
	setScreen(std::make_shared<EditorScreen>());
}

EditorApplication::~EditorApplication()
{
	
}

void EditorApplication::prefix()
{
	EngineCoreApplication::prefix();
	
	//debug
	{
		if (m_debug_window)
		{
			ImGui::ShowMetricsWindow();

		}
	}
}

void EditorApplication::postfix()
{
	EngineCoreApplication::postfix();

}

void EditorApplication::debugButtonWindowPressed(InputType type, int key, int scancode, int action, int mods)
{
	m_debug_window = !m_debug_window;
}
