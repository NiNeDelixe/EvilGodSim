#include "enginecore/core/graphics/render/ModelRenderer.h"

void ModelRenderer::render()
{
	/*EngiApp->ctx().lock()->setDepthTest(true);
	EngiApp->ctx().lock()->setBlendMode(BlendMode::normal);*/
	EngiApp->ctx().lock()->setDepthTest(true);

	//EngiApp->ctx().lock()->setBlendMode(BlendMode::addition);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	const auto& shader = EngiApp->assets().lock()->get<GLShader>("model");

	const auto& player_view = EngiApp->getEntityRegistry().view<ModelComponent, Transform>();

	for (auto&& ent : player_view)
	{
		auto&& mod = EngiApp->getEntityRegistry().get<ModelComponent>(ent);
		auto&& tran = EngiApp->getEntityRegistry().get<Transform>(ent);

		glm::mat4 model = glm::translate(glm::mat4(1.0f)/*base*/, tran.m_pos/*pos*/);
		

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
