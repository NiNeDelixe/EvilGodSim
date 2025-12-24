#include "enginecore/core/assets/AssetsLoader.h"

AssetsLoader::AssetsLoader()
{

}

void AssetsLoader::addResource(const AssetType& tag, const std::string& filename, const std::string& alias, const std::shared_ptr<configs::AssetConfig>& settings)
{
    if (m_enqueued.find({ tag, alias }) != m_enqueued.end())
    {
        return;
    }
    m_entries.push({ tag, filename, alias, settings });
	m_enqueued.insert({ tag, alias });
}

void AssetsLoader::addResources(const std::list<std::filesystem::path>& resources)
{
	for (std::filesystem::path res : resources)
	{
		if (res.extension() == ".png")
		{
			addResource(AssetType::TEXTURE, res.generic_string(), res.stem().generic_string(), nullptr);
			continue;
		}

		if (res.extension() == ".png" && res.filename().string().find("_font") != std::string::npos)
		{
			addResource(AssetType::FONT, res.generic_string(), res.stem().generic_string(), nullptr);
			continue;
		}

		if (res.extension() == ".frag" || res.extension() == ".vert")
		{
			addResource(AssetType::SHADER, res.replace_extension().generic_string(), res.stem().generic_string(), nullptr);
			continue;
			/*if (res.extension() == "vert")
			{
				
			}
			else
			{
				LOG(ERROR) << "Shader must have vert and frag shader file";
			}*/
		}

		if (res.extension() == ".fbx" || res.extension() == ".obj")
		{
			addResource(AssetType::MODEL, res.generic_string(), res.stem().generic_string(), nullptr);
			continue;
		}
	}
}

void AssetsLoader::loadNext()
{	
	const loaderentry& entry = m_entries.front();
	LOG(INFO) << "Loading " << entry.filename << " as " << entry.alias;

	try
	{
		std::shared_ptr<IAssetLoader> loader = getLoader(entry.tag);
		(*loader)(entry.filename, entry.alias, entry.config);
		m_entries.pop();
	}
	catch (const std::exception& exc)
	{
		LOG(ERROR) << exc.what();
		throw std::runtime_error("Exception on " + entry.filename + ", cause: " + exc.what());
	}
}
