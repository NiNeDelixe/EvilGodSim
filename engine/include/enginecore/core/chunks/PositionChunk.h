#pragma once
#ifndef CHUNKS_POSITIONCHUNK_H_
#define CHUNKS_POSITIONCHUNK_H_

#include <glm/ext.hpp>

class PostionChunk
{
public:
	PostionChunk() = default;
	~PostionChunk() = default;

private:
	glm::u64vec3 m_chunk_pos;
};


#endif // !CHUNKS_POSITIONCHUNK_H_