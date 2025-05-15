#pragma once
#ifndef TEXTURE_ATLAS_H_
#define TEXTURE_ATLAS_H_

#include <finders_interface.h>

#include "enginecore/core/assets/texture/Texture.h"

#include "enginecore/utils/math/UVRegion.h"

class Atlas : IAsset
{
public:
	using spaces_type = rectpack2D::empty_spaces<false, rectpack2D::default_empty_spaces>;
	using rect_type = rectpack2D::output_rect_t<spaces_type>;

	class Builder
	{
	public:
		struct atlas_entry 
		{
			std::string m_name;
			std::shared_ptr<ImageData> m_texture;
		};

		friend Atlas;

	private:
		Builder() = default;

	public:
		~Builder() = default;

	public:
		Builder* const addTexture(const std::string& name, const std::shared_ptr<ImageData>& texture);

        /// @brief prepare generate atlas texture (calls .prepare()) 
        Builder* const setPrepare(const bool& state);

        /// @brief maxResolution max atlas resolution
        Builder* const setMaxResolution(const uint_t& resolution);

		bool has(const std::string& name) const { return m_names.find(name) != m_names.end(); }

		/// @brief Build atlas from all added images
		/// @param extrusion textures extrusion pixels 
		/// (greather is less mip-mapping artifacts)
        template<IsTexture TEXTURE, typename... TEXARGS>
		std::shared_ptr<Atlas> build(const uint_t& extrusion, const TEXARGS&&... args)
        {
            std::vector<Atlas::rect_type> rectangles;
            uint_t index = 0;
            for (auto& entry : m_entries)
            {
                auto& image = entry.m_texture;
                rectangles.emplace_back(rectpack2D::rect_xywh(0, 0, image->getWidth(), image->getHeight()));
            }

            const auto max_side = m_max_resolution;
            const auto discard_step = -4;
            const auto runtime_flipping_mode = rectpack2D::flipping_option::ENABLED;

            const auto result_size = rectpack2D::find_best_packing<spaces_type>(
                rectangles,
                rectpack2D::make_finder_input(
                    max_side,
                    discard_step,
                    [](rect_type&) {},
                    [](rect_type&) {},
                    runtime_flipping_mode
                )
            );

            if (result_size.h > m_max_resolution || result_size.w > m_max_resolution)
            {
                throw std::runtime_error(
                    "max atlas resolution " + std::to_string(m_max_resolution) + " exceeded"
                );
            }

            uint_t width = 32;
            uint_t height = 32;

            std::shared_ptr<ImageData> canvas = std::make_shared<ImageData>(ImageData::ImageFormat::rgba8888, width, height);
            std::unordered_map<std::string, UVRegion> regions;
            for (uint_t i = 0; i < m_entries.size(); i++)
            {
                const auto& rect = rectangles[i];
                const atlas_entry& entry = m_entries[i];
                uint_t x = rect.x;
                uint_t y = rect.y;
                uint_t w = rect.w;
                uint_t h = rect.h;
                canvas->blit(*entry.m_texture, x, y);
                for (uint_t j = 0; j < extrusion; j++) {
                    canvas->extrude(x - j, y - j, w + j * 2, h + j * 2);
                }
                float unitX = 1.0f / width;
                float unitY = 1.0f / height;
                regions[entry.m_name] = UVRegion(
                    unitX * x, unitY * y, unitX * (x + w), unitY * (y + h)
                );
            }
            std::shared_ptr<Atlas> atlas = std::make_shared<Atlas>(std::move(canvas), regions);
            if (m_prepare)
            {
                atlas->template prepare<TEXTURE, TEXARGS...>(std::forward<TEXARGS>(args)...);
            }
            return atlas;
        }

	public:
		const std::set<std::string>& getNames() { return m_names; };

	private:
		std::vector<atlas_entry> m_entries;
		std::set<std::string> m_names;

        bool m_prepare = true;
        uint_t m_max_resolution = Texture::MAX_RESOLUTION;
	};

protected:
	Atlas() = default;
	Atlas(const std::shared_ptr<ImageData>& image, const std::unordered_map<std::string, UVRegion>& regions);

public:
	~Atlas() = default;

	template<IsTexture TEXTURE, typename... ARGS>
	void prepare(const ARGS&&... args)
	{
		m_texture = Texture::createFromImageData<TEXTURE, ARGS...>(m_image, std::forward<ARGS>(args)...);
	}

public:
	static std::shared_ptr<Builder> builder() { return std::shared_ptr<Builder>(new Builder()); }

protected:
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<ImageData> m_image;
	std::unordered_map<std::string, UVRegion> m_regions;
};


#endif // !TEXTURE_ATLAS_H_