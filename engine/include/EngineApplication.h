#pragma once
#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

class EngineApplication
{
public:
	EngineApplication(int argc, char** argv);

	EngineApplication() = default;
	virtual ~EngineApplication() = default;

public:
	int exec() noexcept;

public:
	static EngineApplication* instance() { return m_instance; }

private:
	static EngineApplication* m_instance;
};

#if defined(EngiApp)
#undef EngiApp
#endif
#define EngiApp (static_cast<EngineApplication*>(EngineApplication::instance()))

#endif // !ENGINE_ENGINE_H_