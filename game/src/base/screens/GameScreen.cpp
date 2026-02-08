#include "GameScreen.h"

GameScreen::GameScreen()
	: render(std::shared_ptr<Level>(nullptr))
{
	EngiApp->window()->events()->lockCursor(true);
	EngiApp->setEntitySystem(SystemCategory::CAMERA_BEHAVIOR, std::make_shared<ThirdPersonSystem>());
	EngiApp->setEntitySystem(SystemCategory::OBJECT_CONTROLLING, std::make_shared<PlayerControllSystem>());
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
