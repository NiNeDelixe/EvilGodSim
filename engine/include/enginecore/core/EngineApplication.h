#pragma once
#ifndef ENGINE_ENGINEAPPLICATION_H_
#define ENGINE_ENGINEAPPLICATION_H_

#include "EngineCoreApplication.h"

class EngineApplication;
#if defined(EngiApp)
#undef EngiApp
#endif
#define EngiApp (static_cast<EngineApplication*>(EngineCoreApplication::instance()))

class EngineApplication : public EngineCoreApplication
{
public:
	EngineCoreApplication::EngineCoreApplication;

	EngineApplication() = default;
	~EngineApplication() = default;

private:
};

#endif // !ENGINE_ENGINEAPPLICATION_H_