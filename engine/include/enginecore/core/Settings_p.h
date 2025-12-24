#pragma once
#ifndef TYPES_SETTINGS_P_H_
#define TYPES_SETTINGS_P_H_

#include "enginecore/utils/types/Setting.h"

struct AudioSettings
{
    /// @brief try to initialize AL backend
    FlagSetting enabled{ true };

    NumberSetting volume_master{ 1.0f, 0.0f, 1.0f, setting_format::percent };
    NumberSetting volume_regular{ 1.0f, 0.0f, 1.0f, setting_format::percent };
    NumberSetting volume_ui{ 1.0f, 0.0f, 1.0f, setting_format::percent };
    NumberSetting volume_ambient{ 1.0f, 0.0f, 1.0f, setting_format::percent };
    NumberSetting volume_music{ 1.0f, 0.0f, 1.0f, setting_format::percent };
};

struct DisplaySettings
{
    /// @brief Is window in full screen mode
    FlagSetting fullscreen{ false };
    /// @brief Window width (pixels)
    IntegerSetting width{ 1280 };
    /// @brief Window height (pixels)
    IntegerSetting height{ 720 };
    /// @brief Anti-aliasing samples
    IntegerSetting samples{ 0 };
    /// @brief Framerate limit
    IntegerSetting framerate{ -1, -1, 120 };
    /// @brief Limit framerate when window is iconified
    FlagSetting limit_fps_iconified{ true };
};

struct ChunksSettings
{
    /// @brief Max milliseconds that engine uses for chunks loading only
    IntegerSetting load_speed{ 4, 1, 32 };
    /// @brief Radius of chunks loading zone (chunk is unit) 
    IntegerSetting load_distance{ 22, 3, 80 };
    /// @brief Buffer zone where chunks are not unloading (chunk is unit)
    IntegerSetting padding{ 2, 1, 8 };
};

struct CameraSettings
{
    /// @brief Camera dynamic field of view effects
    FlagSetting fov_effects{ true };
    /// @brief Camera movement shake
    FlagSetting shaking{ true };
    /// @brief Camera movement inertia effect
    FlagSetting inertia{ true };
    /// @brief Camera field of view
    NumberSetting fov{ 90.0f, 10.f, 120.f };
    /// @brief Camera sensitivity
    NumberSetting sensitivity{ 2.0f, 0.1f, 10.0f };
};

struct GraphicsSettings
{
    /// @brief Fog opacity is calculated as `pow(depth*k, fogCurve)` where k depends on chunksLoadDistance.
    /// 1.0 is linear, 2.0 is quadratic
    NumberSetting fog_curve{ 1.0f, 1.0f, 6.0f };
    /// @brief Lighting gamma
    NumberSetting gamma{ 1.0f, 0.4f, 1.0f };
    /// @brief Enable blocks backlight to prevent complete darkness
    FlagSetting backlight{ true };
    /// @brief Disable culling with 'optional' mode
    FlagSetting dense_render{ true };
    /// @brief Enable chunks frustum culling
    FlagSetting frustum_culling{ true };
    /// @brief Skybox texture face resolution
    IntegerSetting skybox_resolution{ 64 + 32, 64, 128 };
    /// @brief Chunk renderer vertices buffer capacity
    IntegerSetting chunk_max_vertices{ 200'000, 0, 4'000'000 };
    /// @brief Chunk renderer vertices buffer capacity in dense render mode
    IntegerSetting chunk_max_vertices_dense{ 800'000, 0, 8'000'000 };
    /// @brief Limit of chunk renderers count
    IntegerSetting chunk_max_renderers{ 6, -4, 32 };
};

struct DebugSettings
{
    /// @brief Turns off saving/loading
    FlagSetting generator_test_mode{ false };
    /// @brief Write lights cache
    FlagSetting doWrite_lights{ true };
};

struct UiSettings
{
    StringSetting language{ U"auto" };
    IntegerSetting world_preview_size{ 64, 1, 512 };
};

struct NetworkSettings
{
};


struct EngineSettingsPrivate
{
    std::shared_ptr<AudioSettings> audio = std::make_shared<AudioSettings>();
    std::shared_ptr<DisplaySettings> display = std::make_shared<DisplaySettings>();
    std::shared_ptr<ChunksSettings> chunks = std::make_shared<ChunksSettings>();
    std::shared_ptr<CameraSettings> camera = std::make_shared<CameraSettings>();
    std::shared_ptr<GraphicsSettings> graphics = std::make_shared<GraphicsSettings>();
    std::shared_ptr<DebugSettings> debug = std::make_shared<DebugSettings>();
    std::shared_ptr<UiSettings> ui = std::make_shared<UiSettings>();
    std::shared_ptr<NetworkSettings> network = std::make_shared<NetworkSettings>();
};



#endif // !TYPES_SETTINGS_P_H_