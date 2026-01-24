#include "GameScreen.h"

GameScreen::GameScreen()
	: render(std::shared_ptr<Level>(nullptr))
{
	EngiApp->window()->events()->lockCursor(true);
	EngiApp->setEntitySystem(SystemTypes::CAMERA_BEHAVIOR, std::make_shared<ThirdPersonSystem>());
	EngiApp->setEntitySystem(SystemTypes::OBJECT_CONTROLLING, std::make_shared<PlayerControllSystem>());
}

void GameScreen::update(const float& delta)
{
	//render.generateChunk(0, 0);
	render.render();
}

void GameScreen::draw(const float& delta)
{
	//mesh->draw();
}

void GameScreen::loadTestMap()
{
	
}
