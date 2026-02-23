#pragma once
#ifndef COMPONENTS_MODELCOMPONENT_H_
#define COMPONENTS_MODELCOMPONENT_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/interfaces/IComponent.h"

#include "enginecore/core/graphics/render/Model.h"

class ModelComponent : public IComponent
{
public:
	ModelComponent(const Model* const model) : model(model) {}
	ModelComponent() = default;
	~ModelComponent() = default;

// public:
// 	const Model* const getModel() const {
// 		return this->m_model;
// 	};

// private:
public:
	const Model* const model;
};


#endif // !COMPONENTS_MODELCOMPONENT_H_