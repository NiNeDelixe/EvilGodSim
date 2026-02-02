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
}

void GameApplication::postfix()
{
	EngineCoreApplication::postfix();
}
