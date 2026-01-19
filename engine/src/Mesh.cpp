#include "enginecore/core/graphics/render/Mesh.h"

#include "enginecore/utils/GLUtils.h"

size_t MeshStats::m_draw_calls = 0;
size_t MeshStats::m_meshes_count = 0;
size_t MeshStats::m_triangles_count = 0;