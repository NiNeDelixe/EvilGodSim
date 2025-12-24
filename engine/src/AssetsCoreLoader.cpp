#include "enginecore/core/assets/AssetsCoreLoader.h"

void AssetsCoreLoader::storeShaders()
{
	auto main_shared = GLShader::createFromSource(CoreResources::main_vert, CoreResources::main_frag);
	auto test_shared = GLShader::createFromSource(CoreResources::test_vert, CoreResources::test_frag);
	auto camera_shared = GLShader::createFromSource(CoreResources::camera_vert, CoreResources::camera_frag);
	auto model_shared = GLShader::createFromSource(CoreResources::model_vert, CoreResources::model_frag);
	m_manager.lock()->store<GLShader>(main_shared, "main");
	m_manager.lock()->store<GLShader>(test_shared, "test");
	m_manager.lock()->store<GLShader>(test_shared, "camera");
	m_manager.lock()->store<GLShader>(test_shared, "model");
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