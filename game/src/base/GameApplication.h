#pragma once
#ifndef BASE_GAMEAPPLICATION_H_
#define BASE_GAMEAPPLICATION_H_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <enginecore/core/EngineCoreApplication.h>

#include "base/screens/GameScreen.h"
#include "base/screens/MenuScreen.h"

class GameApplication;
#if defined(EngiApp)
#undef EngiApp
#endif
#define EngiApp (static_cast<GameApplication*>(EngineCoreApplication::instance()))

class GameApplication : public EngineCoreApplication
{
public:
	GameApplication(int argc, char** argv);
	~GameApplication();

public:
	virtual void prefix() override;
	virtual void postfix() override;
};


#endif // !BASE_GAMEAPPLICATION_H_