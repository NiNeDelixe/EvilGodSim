#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator()
{
	std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
	m_seed = time.time_since_epoch().count();

	m_noise.SetSeed(m_seed);
}

void TerrainGenerator::generateChunk(std::shared_ptr<Chunk>& chunk, const int& chunk_x, const int& chunk_z)
{
	noise::utils::NoiseMapBuilderPlane builder;
	builder.SetDestNoiseMap(m_height_map);
	builder.SetSourceModule(m_noise);

	//set chunk coords
	builder.SetBounds(chunk_x, Chunk::CHUNK_WIDTH, chunk_z, Chunk::CHUNK_LENGTH);

	builder.SetDestSize(TerrainGenerator::NOISE_WIDTH, TerrainGenerator::NOISE_LENGHT);

	builder.SetCallback(noise_callback);

	//build hight map
	builder.Build();

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(m_height_map);
	renderer.SetDestImage(image);
	renderer.Render();

	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial.bmp");
	writer.WriteDestFile();
	

	chunk = std::make_shared<Chunk>();
}

void noise_callback(int row)
{
	std::cout << row << std::endl;
}
