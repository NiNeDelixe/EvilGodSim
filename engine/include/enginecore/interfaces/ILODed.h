#pragma once
#ifndef INTERFACES_ILODED_H_
#define INTERFACES_ILODED_H_

#include <unordered_map>

#include "enginecore/core/graphics/lods/LOD.h"

class ILODed
{
public:
	ILODed() = default;
	virtual ~ILODed() = default;

	void addLOD(const size_t& lod_factor, const LOD& lod) 
	{
		m_lods.insert(std::make_pair(lod_factor, lod));
	}

protected:
	std::unordered_map<size_t, LOD> m_lods;
};


#endif // !INTERFACES_ILODED_H_