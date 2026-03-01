#include "enginecore/core/graphics/render/ModelRenderer.h"

void ModelRenderer::render()
{
	auto ldrc = EngiApp->ctx().lock()->sub();

	ldrc.setBlendMode(BlendMode::normal);
	ldrc.setDepthTest(true);
	ldrc.setCullFace(true);

	const auto& shader = EngiApp->assets().lock()->get<GLShader>("model");

	const auto& player_view = EngiApp->getEntityRegistry().view<ModelComponent, Transform>();

	for (auto&& [ent, mod, tran] : player_view.each())
	{
		auto render_trans_c = EngiApp->getEntityRegistry().try_get<RenderTransform>(ent);

		glm::mat4 model;
		if (render_trans_c)
		{
			model = glm::translate(glm::mat4(1.0f)/*base*/, render_trans_c->relative_position/*pos*/);
			model *= glm::toMat4(render_trans_c->relative_rotation);
		}
		else
		{
			model = glm::translate(glm::mat4(1.0f)/*base*/, tran.m_pos/*pos*/);
			model *= tran.m_rotation;
		}
		
		
		

		shader->use();
		shader->uniform("u_color", glm::vec4(0.5f));

		shader->uniform("u_model", model);

		mod.model->draw();
	}

	
}

std::shared_ptr<IMesh> ModelRenderer::createMesh()
{
	return std::shared_ptr<IMesh>();
}
