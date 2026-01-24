#pragma once
#ifndef TEXTURE_TEXTURE_H_
#define TEXTURE_TEXTURE_H_

#include <memory>
#include <iostream>
#include <filesystem>
#include <concepts>
#include <streambuf>

#include "enginecore/core/CoreDefines.h"
#include "enginecore/core/assets/texture/ImageData.h"
#include "enginecore/interfaces/IAsset.h"
#include "enginecore/utils/math/UVRegion.h"

class Texture;

template<typename T>
concept IsTexture = std::derived_from<T, Texture>;

class Texture : public IAsset
{
public:
	/// <summary>
	/// always first height and width
	/// </summary>
	Texture(const uint_t& height, const uint_t& width);
	Texture() = delete;
	Texture(const Texture& copy) = delete;
	~Texture() = default;

public:
	template<IsTexture TEXTURE, typename... ARGS>
	static std::shared_ptr<Texture> createFromFile(const std::filesystem::path& path_to_file, const ARGS&&... args)
	{
		std::shared_ptr<ImageData> data = ImageData::createFromFile(path_to_file);
		
		return createFromImageData<TEXTURE, ARGS...>(data, std::forward<ARGS>(args)...);
	}

	template<IsTexture TEXTURE, typename... ARGS>
	static std::shared_ptr<Texture> createFromRawData(const std::shared_ptr<ubyte_t[]>& raw_array, const ARGS&&... args)
	{
		std::shared_ptr<Texture> texture = std::make_shared<TEXTURE, ARGS...>(std::forward<ARGS>(args)...);
		texture->m_image_data->m_format = ImageData::ImageFormat::rgba8888;
		texture->m_image_data->m_bytes = raw_array;
		texture->load();
		return texture;
	}

	template<IsTexture TEXTURE, typename... ARGS>
	static std::shared_ptr<Texture> createFromRawData(const ubyte_t raw_array[], ARGS&&... args)
	{
		std::shared_ptr<Texture> texture = std::make_shared<TEXTURE, ARGS...>(std::forward<ARGS>(args)...);

		size_t size = texture->m_image_data->getDataSize();
		std::shared_ptr<ubyte_t[]> array = std::make_shared<ubyte_t[]>(size);
		for (size_t i = 0; i < size; i++)
		{
			array[i] = raw_array[i];
		}
		
		std::shared_ptr<ImageData> new_image = std::make_shared<ImageData>(ImageData::ImageFormat::rgba8888,
			texture->m_image_data->getWidth(), texture->m_image_data->getHeight(), array);

		texture->m_image_data = new_image;

		texture->load();
		return texture;
	}

	template<IsTexture TEXTURE, typename... ARGS>
	static std::shared_ptr<Texture> createFromImageData(const std::shared_ptr<ImageData>& image_data, const ARGS&&... args)
	{
		std::shared_ptr<Texture> texture = std::make_shared<TEXTURE, ARGS...>(image_data->getHeight(), image_data->getWidth(),
			std::forward<ARGS>(args)...);
		texture->m_image_data = image_data;
		texture->load();
		return texture;
	}

protected:
	virtual void load() {}

public:
	virtual void bind() const { throw std::logic_error(std::string(__FUNCTION__) + " function not implemented."); }
	virtual void unbind() const { throw std::logic_error(std::string(__FUNCTION__) + " function not implemented."); }
	virtual void reload() { throw std::logic_error(std::string(__FUNCTION__) + " function not implemented."); }

public:
	const std::shared_ptr<ubyte_t[]>& getBytesArray() { return m_image_data->getBytesArray(); }
	const std::weak_ptr<ImageData>& getImageData() { return m_image_data; }

	const UVRegion getUVRegion() const { return UVRegion(0.0f, 0.0f, 1.0f, 1.0f); }

	const uint_t& getWidth() const { return m_image_data->getWidth(); }
	const uint_t& getHeight() const { return m_image_data->getHeight(); }

public:
	inline static uint_t MAX_RESOLUTION = 1024;

protected:
	std::shared_ptr<ImageData> m_image_data;
};


#endif // !TEXTURE_TEXTURE_H_