#pragma once
#ifndef BASE_EDITORAPPLICATION_H_
#define BASE_EDITORAPPLICATION_H_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <enginecore/core/EngineCoreApplication.h>

#include "base/screens/EditorScreen.h"

class EditorApplication;
#if defined(EngiApp)
#undef EngiApp
#endif
#define EngiApp (static_cast<EditorApplication*>(EngineCoreApplication::instance()))

class EditorApplication : public EngineCoreApplication
{
public:
	EditorApplication(int argc, char** argv);
	~EditorApplication();

public:
	virtual void prefix() override;
	virtual void postfix() override;

public:
	void debugButtonWindowPressed(InputType type, int key, int scancode, int action, int mods);

private:
	bool m_debug_window = false;
};


#endif // !BASE_EDITORAPPLICATION_H_