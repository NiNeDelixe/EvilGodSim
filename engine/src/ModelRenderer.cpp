#include "enginecore/core/graphics/render/ModelRenderer.h"

void ModelRenderer::render()
{
	auto ldrc = EngiApp->ctx().lock()->sub();

	ldrc.setBlendMode(BlendMode::normal);
	//ldrc.setBlendMode(BlendMode::addition);
	//ldrc.setBlendMode(BlendMode::inversion);
	ldrc.setDepthTest(true);
	ldrc.setCullFace(true);

	ldrc.getBatch2D()->begin();
	ldrc.getBatch2D()->rect(1, 1, 2, 3);
	ldrc.getBatch2D()->flush();

	const auto& shader = EngiApp->assets().lock()->get<GLShader>("model");

	const auto& player_view = EngiApp->getEntityRegistry().view<ModelComponent, Transform>();

	for (auto&& [ent, mod, tran] : player_view.each())
	{
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
