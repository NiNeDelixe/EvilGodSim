#include "enginecore/core/graphics/render/ModelRenderer.h"

void ModelRenderer::render()
{
	auto ldrc = EngiApp->ctx().lock()->sub();

	//ldrc.setBlendMode(BlendMode::normal);
	//ldrc.setBlendMode(BlendMode::addition);
	ldrc.setBlendMode(BlendMode::inversion);
	ldrc.setDepthTest(true);
	ldrc.setCullFace(true);

	const auto& shader = EngiApp->assets().lock()->get<GLShader>("model");

	const auto& player_view = EngiApp->getEntityRegistry().view<ModelComponent, Transform>();

	for (auto&& ent : player_view)
	{
		auto&& mod = EngiApp->getEntityRegistry().get<ModelComponent>(ent);
		auto&& tran = EngiApp->getEntityRegistry().get<Transform>(ent);

		glm::mat4 model = glm::translate(glm::mat4(1.0f)/*base*/, tran.m_pos/*pos*/);
		model *= tran.m_rotation;
		

		shader->use();
		shader->uniform("u_color", glm::vec4(0.5f));

		shader->uniform("u_model", model);

		mod.getModel()->draw();
	}

	
}

std::shared_ptr<IMesh> ModelRenderer::createMesh()
{
	return std::shared_ptr<IMesh>();
}
