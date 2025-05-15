#pragma once
#ifndef ASSETS_ASSETSCORELOADER_H_
#define ASSETS_ASSETSCORELOADER_H_

#include "enginecore/core/assets/AssetsManager.h"

#include "enginecore/core/assets/texture/GLTexture.h"
#include "enginecore/core/assets/shader/GLShader.h"

#include "missing_texture.h"
#include "main_frag.h"
#include "main_vert.h"

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