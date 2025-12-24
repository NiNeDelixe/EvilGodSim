#include "GameApplication.h"

GameApplication::GameApplication(int argc, char** argv)
	: EngineCoreApplication(argc, argv)
{
	setScreen(std::make_shared<MenuScreen>());
}

GameApplication::~GameApplication()
{

}

void GameApplication::prefix()
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

void GameApplication::postfix()
{
	EngineCoreApplication::postfix();

}

void GameApplication::debugButtonWindowPressed(InputType type, int key, int scancode, int action, int mods)
{
	m_debug_window = !m_debug_window;
}
