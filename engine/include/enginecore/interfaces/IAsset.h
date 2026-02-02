#pragma once
#ifndef INTERFACES_IASSET_H_
#define INTERFACES_IASSET_H_

#include "enginecore/core/CoreDefines.h"

#include <string>
#include <filesystem>

enum class AssetType { TEXTURE, SHADER, FONT, ATLAS, LAYOUT, SOUND, MODEL };

class IAsset
{
protected:
	IAsset() = default;

public:
	virtual ~IAsset() = default;

	virtual std::string toString() const { return getType(); }
	const std::string getType() const { return typeid(*this).name(); }
	virtual const bool& isLoaded() const { return m_is_loaded; }

	virtual void reload() {}

	virtual GETTER(std::filesystem::path, m_asset_path, Path);
	virtual SETTER(std::filesystem::path, m_asset_path, Path);

protected:
	std::filesystem::path m_asset_path;
	bool m_is_loaded;
};

#endif // !INTERFACES_IASSET_H_