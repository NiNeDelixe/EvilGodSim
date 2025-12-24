#include "enginecore/core/assets/AssetsRegistry.h"

std::weak_ptr<EnginePaths> AssetsRegistry::m_paths = EngiApp->paths();
std::weak_ptr<AssetsManager> AssetsRegistry::m_manager = EngiApp->assets();
std::weak_ptr<AssetsLoader> AssetsRegistry::m_loader = EngiApp->getAssetsLoader();
