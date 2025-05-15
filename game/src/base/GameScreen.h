#pragma once
#ifndef BASE_GAMESCREEN_H_
#define BASE_GAMESCREEN_H_

#include <enginecore/core/screens/Screen.h>

#include <enginecore/core/EngineCoreApplication.h>

class GameScreen : public Screen
{
public:
	GameScreen() = default;
	~GameScreen() = default;

	void update(const float& delta) override;
	void draw(const float& delta) override;

private:

};


#endif // !BASE_GAMESCREEN_H_