#pragma once
#ifndef ASSETS_ASSETSLOADER_H_
#define ASSETS_ASSETSLOADER_H_

#include <map>
#include <memory>
#include <queue>

#include <glog/logging.h>

#include "enginecore/interfaces/IAssetLoader.h"

/// <summary>
/// Load assets from packages 
/// <para/>!!not load core assets!!
/// <para/>for loading core use specific class
/// </summary>
class AssetsLoader
{
public:
	struct loaderentry 
	{
		AssetType tag;
		std::string filename;
		std::string alias;
		std::shared_ptr<configs::AssetConfig> config;
	};

private:
	AssetsLoader();

public:
	~AssetsLoader() = default;

public:
	static const std::shared_ptr<AssetsLoader> instance() { return m_instance; }

	void addLoader(const AssetType& tag, const std::shared_ptr<IAssetLoader>& loader)
	{
		m_loaders[tag] = loader;
	}

	std::shared_ptr<IAssetLoader> getLoader(const AssetType& tag)
	{
		auto found = m_loaders.find(tag);
		if (found == m_loaders.end()) 
		{
			throw std::runtime_error(
				"Unknown asset tag " + std::to_string(static_cast<int>(tag)));
		}
		return found->second;
	}

	void addResource(const AssetType& tag, const std::string& filename, const std::string& alias,
		const std::shared_ptr<configs::AssetConfig>& settings);
	void addResources(const std::list<std::filesystem::path>& resources);

	bool hasNext() const { return !m_entries.empty(); }
	void loadNext();

	void load()
	{
		while (hasNext())
		{
			loadNext();
		}
	}
	

private:
	template <class _Ty, class... _Types>
		requires requires(_Ty* _Location, _Types&&... _Args) {
		::new (static_cast<void*>(_Location)) _Ty(_STD forward<_Types>(_Args)...); // per LWG-3888
	}
	friend constexpr _Ty* std::construct_at(_Ty* const _Location, _Types&&... _Args) noexcept(noexcept(::new (static_cast<void*>(_Location)) _Ty(_STD forward<_Types>(_Args)...)));
	template <class _Ty, class... _Types>
	friend _CONSTEXPR20 void std::_Construct_in_place(_Ty& _Obj, _Types&&... _Args);

	std::map<AssetType, std::shared_ptr<IAssetLoader>> m_loaders;
	std::queue<loaderentry> m_entries;
	std::set<std::pair<AssetType, std::string>> m_enqueued;

	static inline std::shared_ptr<AssetsLoader> m_instance = std::make_shared<AssetsLoader>();
};


#endif // !ASSETS_ASSETSLOADER_H_