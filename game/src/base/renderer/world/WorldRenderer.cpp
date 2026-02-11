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
	EngiApp->getEntityRegistry().emplace<PlayerComponent>(entity);

	for (size_t i = 0; i < 10; i++)
	{
		auto&& entity2 = EngiApp->getEntityRegistry().create();
		auto&& model2 = EngiApp->assets().lock()->get<Model>("spider");
		
		EngiApp->getEntityRegistry().emplace<ModelComponent>(entity2, model2);
		EngiApp->getEntityRegistry().emplace<Transform>(entity2);
	}
	

	
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
	const auto& camera_views = EngiApp->getEntityRegistry().view<Camera, Transform>();
	//const auto& model_views = EngiApp->getEntityRegistry().view<const ModelComponent, Transform>();
	const auto& viewport = EngiApp->window()->viewports()[0];
	
	for (auto [camera_entity, camera, camera_transform] : camera_views.each())
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f)/*base*/, camera_transform.m_pos/*pos*/);
		model *= camera_transform.m_rotation;

		camera.setAspectRatio(viewport->getWidth() / static_cast<float>(viewport->getHeight()));
		//camera.setAspectRatio(viewport->getHeight() / static_cast<float>(viewport->getWidth()));

		shader->use();
		//frag
		//shader->uniform("u_lightDirection", glm::vec3(1));
		//shader->uniform("u_baseColor", glm::vec3(1));
		shader->uniform("u_color", glm::vec4(1.f));

		//vert
		shader->uniform("u_model", model);
		shader->uniform("u_projection", camera.getProjection());
		shader->uniform("u_view", camera.getView());
		//shader->uniform("u_normal", glm::mat3(1));


	}
}
