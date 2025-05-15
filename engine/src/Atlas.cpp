#include "enginecore/core/assets/texture/Atlas.h"

Atlas::Builder* const Atlas::Builder::addTexture(const std::string& name, const std::shared_ptr<ImageData>& texture)
{
	m_entries.emplace_back(name, texture);
	m_names.insert(name);
	return this;
}

Atlas::Builder* const Atlas::Builder::setPrepare(const bool& state)
{
	m_prepare = state;
	return this;
}

Atlas::Builder* const Atlas::Builder::setMaxResolution(const uint_t& resolution)
{
	m_max_resolution = resolution;
	return this;
}

Atlas::Atlas(const std::shared_ptr<ImageData>& image, const std::unordered_map<std::string, UVRegion>& regions)
	: m_image(image), m_regions(regions), m_texture(nullptr)
{
}
