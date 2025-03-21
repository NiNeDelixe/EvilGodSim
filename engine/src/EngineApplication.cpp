#include "EngineApplication.h"

EngineApplication* EngineApplication::m_instance = nullptr;

EngineApplication::EngineApplication(int argc, char** argv)
{
	EngineApplication::m_instance = this;
}

int EngineApplication::exec() noexcept
{
	return 0;
}
