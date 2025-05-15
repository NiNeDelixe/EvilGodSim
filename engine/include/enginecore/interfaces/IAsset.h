#pragma once
#ifndef INTERFACES_IASSET_H_
#define INTERFACES_IASSET_H_

#include <string>
#include <filesystem>

enum class AssetType { TEXTURE, SHADER, FONT, ATLAS, LAYOUT, SOUND, MODEL };

class IAsset
{
protected:
	IAsset() = default;

public:
	virtual ~IAsset() = default;

	virtual const std::string& toString() const { return getType(); }
	const std::string& getType() const { return typeid(*this).name(); }
	virtual const std::filesystem::path& getPath() const { return m_asset_path; }
	virtual const bool& isLoaded() const { return m_is_loaded; }

private:
	std::filesystem::path m_asset_path;
	bool m_is_loaded;
};

#endif // !INTERFACES_IASSET_H_