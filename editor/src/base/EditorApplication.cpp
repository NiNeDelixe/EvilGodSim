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
}

void EditorApplication::postfix()
{
	EngineCoreApplication::postfix();

}
