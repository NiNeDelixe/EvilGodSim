#include "enginecore/core/assets/texture/Texture.h"

Texture::Texture(const uint_t& height, const uint_t& width)
{
	m_image_data = std::make_shared<ImageData>(ImageData::ImageFormat::rgba8888, width, height);
}
