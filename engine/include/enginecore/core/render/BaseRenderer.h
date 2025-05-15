#pragma once
#ifndef RENDER_BASERENDERER_H_
#define RENDER_BASERENDERER_H_

#include <memory>
#include <variant>
#include <list>

#include <glm/glm.hpp>

#include "enginecore/interfaces/IMesh.h"

class BaseRenderer
{
public:
	BaseRenderer(const size_t& capacity) 
		: m_capacity(capacity) {};
	virtual ~BaseRenderer() = default;

public:
	virtual std::shared_ptr<IMesh> createMesh() = 0;
	virtual void render() = 0;

protected:
	virtual void vertex(const glm::vec3& coord, const float& u, const float& v, const glm::vec4& light);
	virtual void index(const int& a, const int& b, const int& c, const int& d, const int& e, const int& f);
	virtual void vertexAO(const glm::vec3& coord, const float& u, const float& v, const glm::vec4& brightness,
		const glm::vec3& axisX, const glm::vec3& axisY, const glm::vec3& axisZ);

	virtual glm::vec4 pickSoftLight(const glm::ivec3& coord, const glm::ivec3& right, const glm::ivec3& up) const;
	virtual glm::vec4 pickLight(const int& x, const int& y, const int& z) const;
	virtual glm::vec4 pickLight(const glm::ivec3& coord) const;

protected:
	std::list<std::shared_ptr<IMesh>> m_meshes;
	std::shared_ptr<float[]> m_vertex_buffer = std::make_shared<float[]>(m_capacity);
	std::shared_ptr<int[]> m_index_buffer = std::make_shared<int[]>(m_capacity);
	size_t m_vertex_offset = 0;
	size_t m_index_offset = 0;
	size_t m_index_size = 0;
	size_t m_capacity = 0;
	bool m_overflow = false;
	bool m_cancelled = false;
};

#endif // !RENDER_BASERENDERER_H_