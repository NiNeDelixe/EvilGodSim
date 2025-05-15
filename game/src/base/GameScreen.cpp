#include "GameScreen.h"

void GameScreen::update(const float& delta)
{
	auto shader = EngiApp->assets().lock()->get<GLShader>("Styled");
	//shader->uniform();
}

void GameScreen::draw(const float& delta)
{
}
