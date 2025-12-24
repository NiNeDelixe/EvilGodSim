#pragma once
#ifndef ASSETS_ASSETSREGISTRY_H_
#define ASSETS_ASSETSREGISTRY_H_

#include "enginecore/core/CoreDefines.h"

#include <string>
#include <memory>
#include <concepts>

#include "enginecore/interfaces/IAsset.h"
#include "enginecore/interfaces/IGameAsset.h"

#include "enginecore/core/assets/AssetsManager.h"
#include "enginecore/core/assets/AssetsLoader.h"
#include "enginecore/core/assets/Identifier.h"

#include "enginecore/core/EnginePaths.h"

#include "enginecore/core/EngineCoreApplication.h"

namespace CONCEPTS_NAMESPACE
{
	template<class T>
	concept IsDerivedFromIGameAsset = std::derived_from<T, IGameAsset>;
}

class AssetsRegistry
{
public:
	struct GameAssetType
	{
	};

public:
	AssetsRegistry() = default;
	~AssetsRegistry() = delete;

public:
	template<CONCEPTS_NAMESPACE::IsDerivedFromIGameAsset T>
	static std::shared_ptr<T> registry(const AssetsRegistry::GameAssetType& type,
		const std::shared_ptr<Identifier>& identifier, const std::shared_ptr<T>& asset_class)
	{
		//identifier->getAssetName();
		//m_loader.lock()->addResource();
		return asset_class;
	}

private:
	static std::weak_ptr<EnginePaths> m_paths;
	static std::weak_ptr<AssetsManager> m_manager;
	static std::weak_ptr<AssetsLoader> m_loader;
};



#endif // !ASSETS_ASSETSREGISTRY_H_