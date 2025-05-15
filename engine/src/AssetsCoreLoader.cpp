#include "enginecore/core/assets/AssetsCoreLoader.h"

void AssetsCoreLoader::storeShaders()
{
	auto shared = GLShader::createFromSource(CoreResources::main_vert, CoreResources::main_frag);
	m_manager.lock()->store<GLShader>(shared, "main");
}

void AssetsCoreLoader::storeTextures()
{
	auto texture = Texture::template createFromRawData<GLTexture>(
		CoreResources::missing_texture, 16u, 16u);
	m_manager.lock()->store<Texture>(texture, "missing");
}

void AssetsCoreLoader::load()
{
	storeShaders();
	storeTextures();
}