#pragma once
#ifndef UTILS_IMGUIINCLUDES_H_
#define UTILS_IMGUIINCLUDES_H_

#include "enginecore/utils/platform/CompilerDetection.h"
#include "enginecore/utils/platform/GLDetection.h"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

//#include "imgui_impl_dx11.h"

#ifdef E_OS_WIN32
#include <imgui_impl_win32.h>
#endif // E_OS_WIN32

#ifdef E_OS_DARWIN
//#include "imgui_impl_metal.h"
#endif // E_OS_DARWIN

#ifdef E_GL_GLFW
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif // E_GL_GLFW



#endif // !UTILS_IMGUIINCLUDES_H_