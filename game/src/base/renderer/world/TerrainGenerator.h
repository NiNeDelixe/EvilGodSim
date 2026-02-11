#pragma once
#ifndef WORLD_TERRAINGENERATOR_H_
#define WORLD_TERRAINGENERATOR_H_

#include <memory>
#include <chrono>

#include <iomanip>
#include <iostream>

#include <noise/noise.h>
#include <noise/noiseutils.h>

#include "base/renderer/world/Chunk.h"

void noise_callback(int row);

class TerrainGenerator 
{
private:
    struct Params
    {
        ///@brief Noise scale
        float noise_scale = 0.03f;
        ///@brief average hight
        int base_height = 64;
        ///@brief max hight
        float amplitude = 12.0f;
        ///@brief smooth hight and lowest
        float smoothness = 2.0f;
        ///@brief level under generate stones
        int ground_level = 60;
    };

public:
    TerrainGenerator();
    ~TerrainGenerator() = default;

    void generateChunk(std::shared_ptr<Chunk>& chunk, const int& chunk_x, const int& chunk_z);
    void setSeed(const uint64_t& seed) { m_seed = seed; m_noise.SetSeed(m_seed); }


public:
    Params m_params;

    inline static size_t NOISE_WIDTH = 256;
    inline static size_t NOISE_LENGHT = 256;

private:
    noise::module::Perlin m_noise;
    noise::utils::NoiseMap m_height_map;
    uint64_t m_seed;
};

#endif // !WORLD_TERRAINGENERATOR_H_