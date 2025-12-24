#pragma once
#ifndef ASSETS_ASSETSCORELOADER_H_
#define ASSETS_ASSETSCORELOADER_H_

#include "enginecore/core/assets/AssetsManager.h"

#include "enginecore/core/assets/texture/GLTexture.h"
#include "enginecore/core/assets/shader/GLShader.h"

#include "missing_texture.h"
#include "main_frag.h"
#include "main_vert.h"
#include "test_frag.h"
#include "test_vert.h"
#include "camera_vert.h"
#include "camera_frag.h"
#include "model_vert.h"
#include "model_frag.h"

class AssetsCoreLoader
{
public:
	AssetsCoreLoader(const std::weak_ptr<AssetsManager>& manager)
		: m_manager(manager) { }
	~AssetsCoreLoader() = default;

private:
	void storeShaders();
	void storeTextures();

public:
	void load();

private:
	std::weak_ptr<AssetsManager> m_manager;
};


#endif // !ASSETS_ASSETSCORELOADER_H_