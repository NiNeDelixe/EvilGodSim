#include "enginecore/core/assets/AssetsLoader.h"

AssetsLoader::AssetsLoader()
{
	//m_instance = this;
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

void AssetsLoader::addResourcesFromContent(const std::filesystem::path &resources_root)
{
	std::filesystem::path content_path = resources_root / "content.json";

	if (!std::filesystem::exists(content_path))
	{
		throw std::runtime_error("resources/content.json not found");
	}

	std::ifstream content_stream(content_path);
	if (!content_stream.is_open())
	{
		throw std::runtime_error("failed to open content file: " + content_path.generic_string());
	}

	Json content = Json::parse(content_stream, nullptr, true, true);

	auto load_array = [&](const char* key, auto handler)
	{
		if (!content.contains(key))
		{
			return;
		}

		const Json& array = content[key];
		if (!array.is_array())
		{
			throw std::runtime_error(std::string("content field is not array: ") + key);
		}

		for (const auto& entry : array)
		{
			if (!entry.is_string())
			{
				LOG(WARNING) << "Skip non-string entry in " << key;
				continue;
			}
			handler(entry.get<std::string>());
		}
	};

	load_array("shaders", [&](const std::string& name)
	{
		const std::filesystem::path shader_base = resources_root / "shaders" / name;
		const std::filesystem::path vertex = shader_base.string() + ".vert";
		const std::filesystem::path fragment = shader_base.string() + ".frag";
		if (!std::filesystem::exists(vertex) || !std::filesystem::exists(fragment))
		{
			LOG(WARNING) << "Shader from content manifest was not found: " << name;
			return;
		}
		addResource(AssetType::SHADER, shader_base.generic_string(), name, nullptr);
	});

	load_array("models", [&](const std::string& name)
	{
		const std::filesystem::path model_base = resources_root / "models" / name;
		const std::array<std::string, 4> extensions = { ".fbx", ".obj", ".gltf", ".glb" };
		for (const auto& extension : extensions)
		{
			const std::filesystem::path candidate = model_base.string() + extension;
			if (std::filesystem::exists(candidate))
			{
				addResource(AssetType::MODEL, candidate.generic_string(), name, nullptr);
				return;
			}
		}

		LOG(WARNING) << "Model from content manifest was not found: " << name;
	});

	load_array("lang", [&](const std::string& name)
	{
		const std::filesystem::path lang_base = resources_root / "lang" / name;
		const std::array<std::string, 3> extensions = { ".json", ".toml", ".txt" };
		for (const auto& extension : extensions)
		{
			if (std::filesystem::exists(lang_base.string() + extension))
			{
				LOG(INFO) << "Language entry found in content manifest: " << name;
				return;
			}
		}
		LOG(WARNING) << "Language entry from content manifest was not found: " << name;
	});
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
