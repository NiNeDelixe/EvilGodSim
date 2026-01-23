#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(const std::weak_ptr<Level>& world)
	: m_world(world)
{
	m_model_renderer = std::make_shared<ModelRenderer>();

	//TESTED
	auto&& entity = EngiApp->getEntityRegistry().create();
	auto&& model = EngiApp->assets().lock()->get<Model>("body_v2");
	
	EngiApp->getEntityRegistry().emplace<ModelComponent>(entity, model);
	EngiApp->getEntityRegistry().emplace<Transform>(entity);
}

void WorldRenderer::render()
{
	prepareShaders();
	//m_world.lock()->
	m_model_renderer->render();
}

void WorldRenderer::prepareShaders()
{
	const auto& shader = EngiApp->assets().lock()->get<GLShader>("camera");
	const auto& camera_views = EngiApp->getEntityRegistry().view<Camera>();
	const auto& model_views = EngiApp->getEntityRegistry().view<ModelComponent, Transform>();
	const auto& viewport = EngiApp->window()->viewports()[0];
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f)/*base*/, glm::vec3(1.f)/*pos*/);

	for (auto&& entity : model_views)
	{
		auto&& transform = model_views.get<Transform>(entity);

		shader->use();

		model = glm::translate(glm::mat4(1.0f)/*base*/, transform.m_pos/*pos*/);
		model *= transform.m_rotation;
		shader->uniform("u_model", model);
	}

	for (auto& entity : camera_views)
	{
		Camera& camera = camera_views.get<Camera>(entity);
		camera.setAspectRatio(viewport->getWidth() / static_cast<float>(viewport->getHeight()));
		//camera.setAspectRatio(viewport->getHeight() / static_cast<float>(viewport->getWidth()));

		shader->use();
		//frag
		//shader->uniform("u_lightDirection", glm::vec3(1));
		//shader->uniform("u_baseColor", glm::vec3(1));
		shader->uniform("u_color", glm::vec4(0.5f));

		//vert
		shader->uniform("u_model", model);
		shader->uniform("u_projection", camera.getProjection());
		shader->uniform("u_view", camera.getView());
		//shader->uniform("u_normal", glm::mat3(1));

	}
}
