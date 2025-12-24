#pragma once
#ifndef SCREEN_MENUSCREEN_H_
#define SCREEN_MENUSCREEN_H_

#include <enginecore/core/CoreDefines.h>

#include <imgui.h>
#include <glog/logging.h>

#include <enginecore/core/EngineCoreApplication.h>

#include <enginecore/core/screens/Screen.h>

#include "base/screens/GameScreen.h"


class MenuScreen : public Screen
{
public:
	MenuScreen();
	~MenuScreen() = default;

	void update(const float& delta) override;
	void draw(const float& delta) override;

private:
	
};

#endif // !SCREEN_MENUSCREEN_H_