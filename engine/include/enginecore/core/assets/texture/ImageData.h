#pragma once
#ifndef TEXTURE_IMAGEDATA_H_
#define TEXTURE_IMAGEDATA_H_

#include <stdexcept>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <memory>
#include <filesystem>

#include <opencv2/opencv.hpp>

#include <glm/vec4.hpp>

#include "enginecore/core/CoreDefines.h"

class ImageData
{
public:
	enum class ImageFormat
	{
		rgb888,
		rgba8888
	};

public:
	ImageData(const ImageFormat& format, const uint_t& width, const uint_t& height);
	ImageData(const ImageFormat& format, const uint_t& width, const uint_t& height, const std::shared_ptr<ubyte_t[]>& data);
	~ImageData() = default;

	static std::shared_ptr<ImageData> createFromFile(const std::filesystem::path& path_to_file);

public:
	void flipByX();
	void flipByY();

	void drawLine(const int& x1, const int& y1, const int& x2, const int& y2, const glm::ivec4& color);
	void blit(const ImageData& image, const int& x, const int& y);
	void extrude(const int& x, const int& y, const int& w, const int& h);
	void fixAlphaColor();

private:
	void blitRGBOnRGBA(const ImageData& image, const int& x, const int& y);
	void blitMatchingFormat(const ImageData& image, const int& x, const int& y) const;

	static bool clipLine(int& x1, int& y1, int& x2, int& y2, const int& width, const int& height);

	template<uint_t channels>
	static void drawLine(ImageData& image, const int& x1, const int& y1, const int& x2, const int& y2, const glm::ivec4& color)
	{
		auto& data = image.getBytesArray();
		uint_t width = image.getWidth();
		uint_t height = image.getHeight();

		int x1_ = x1;
		int y1_ = y1;
		int x2_ = x2;
		int y2_ = y2;

		if ((x1 < 0 || x1 >= width || x2 < 0 || x2 >= width ||
			y1 < 0 || y1 >= height || y2 < 0 || y2 >= height) &&
			!clipLine(x1_, y1_, x2_, y2_, width, height)) 
		{
			return;
		}

		int dx = std::abs(x2_ - x1_);
		int dy = -std::abs(y2_ - y1_);
		int sx = x1_ < x2_ ? 1 : -1;
		int sy = y1_ < y2_ ? 1 : -1;
		int err = dx + dy;

		while (true) 
		{
			size_t pos = (y1_ * width + x1_) * channels;
			for (int i = 0; i < channels; i++) 
			{
				data[pos + i] = color[i];
			}
			if (x1_ == x2_ && y1_ == y2_) 
				break;

			int e2 = 2 * err;
			if (e2 >= dy) 
			{
				err += dy;
				x1_ += sx;
			}
			if (e2 <= dx) 
			{
				err += dx;
				y1_ += sy;
			}
		}
	}

public:
	const uint_t& getWidth() const { return m_width; }
	const uint_t& getHeight() const { return m_height; }
	const std::shared_ptr<ubyte_t[]>& getBytesArray() { return m_bytes; }
	const ImageFormat& getFormat() const { return m_format; }

	size_t getDataSize() const 
	{
		size_t channels = 3 + (m_format == ImageFormat::rgba8888);
		return m_width * m_height * channels;
	}

private:
	ImageFormat m_format{};
	uint_t m_width = 0;
	uint_t m_height = 0;

	std::shared_ptr<ubyte_t[]> m_bytes = nullptr;
};


#endif // !TEXTURE_IMAGEDATA_H_