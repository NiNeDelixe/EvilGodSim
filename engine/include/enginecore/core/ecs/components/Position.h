#pragma once
#ifndef COMPONENTS_POSITION_H_
#define COMPONENTS_POSITION_H_

#include "enginecore/interfaces/IComponent.h"

class Position : public IComponent
{
public:
	float m_x;
	float m_y;
	float m_z;
};


#endif // !COMPONENTS_POSITION_H_