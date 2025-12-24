#include "enginecore/core/EngineApplication.h"

EngineCoreApplication* EngineCoreApplication::m_instance = nullptr;

EngineCoreApplication::EngineCoreApplication(int& argc, char** argv)
	: EngineCoreApplication()
{
	if (!std::filesystem::exists(ENGINE_LOGS_DIRECTORY))
	{
		std::filesystem::create_directory(ENGINE_LOGS_DIRECTORY);
	}

	google::SetLogDestination(google::GLOG_INFO, (std::string(ENGINE_LOGS_DIRECTORY) + "/info_").c_str());
	google::SetLogDestination(google::GLOG_WARNING, (std::string(ENGINE_LOGS_DIRECTORY) + "/warning_").c_str());
	google::SetLogDestination(google::GLOG_ERROR, (std::string(ENGINE_LOGS_DIRECTORY) + "/error_").c_str());
	google::SetLogDestination(google::GLOG_FATAL, (std::string(ENGINE_LOGS_DIRECTORY) + "/fatal_").c_str());

	FLAGS_alsologtostderr = true;
	FLAGS_minloglevel = 0;
	FLAGS_log_prefix = true;
	FLAGS_log_dir = ENGINE_LOGS_DIRECTORY;
	FLAGS_logfile_mode = 0600;

	google::InitGoogleLogging(argv[0]);

	auto a = std::make_shared<DisplaySettings>(); //TEMP: in future its moved to global options and weak_ptr in BaseWindow doesnt expired
	this->m_window = std::make_shared<BaseWindow>(m_global_settings->display(), argv[0]);

	this->m_paths = std::make_shared<EnginePaths>();

	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		this->m_gui_context = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.DisplaySize = { static_cast<float>(this->m_window->viewports()[0]->getWidth()),
			static_cast<float>(this->m_window->viewports()[0]->getHeight()) };

		ImGui_ImplGlfw_InitForOpenGL(this->m_window->getGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	this->m_assets_manager = AssetsManager::instance();

	this->m_assets_loader = AssetsLoader::instance();


	this->m_assets_loader.lock()->addResources(m_paths->listResources());

	setScreen(std::make_shared<PlaceHolderScreen>());	

	loadAssets();
	loadSystems();

	this->m_ctx = std::make_shared<DrawContext>(nullptr, this->m_window);
}

EngineCoreApplication::EngineCoreApplication()
{
	m_global_settings = std::make_shared<EngineSettings>();

	if (EngineCoreApplication::m_instance != nullptr)
	{
		throw std::runtime_error("Engine application must be one instance");
	}
	EngineCoreApplication::m_instance = this;
}

EngineCoreApplication::~EngineCoreApplication()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext(this->m_gui_context);
}

int EngineCoreApplication::exec() noexcept(false)
{
	this->m_in_exec = true;

	this->poll();
	try
	{
	}
	catch (const std::exception& exc)
	{
		LOG(ERROR) << "Exception in main loop cough: " << exc.what();
		throw exc;
	}
	

	this->m_in_exec = false;
	return this->m_return_code;
}

void EngineCoreApplication::quit(const int& return_code)
{
	this->m_return_code = return_code;
	this->m_window->setShouldClose(true);
}

void EngineCoreApplication::poll()
{
	while (!this->m_window->shouldClose())
	{
		Time::update(m_window->time()); //Update time

		this->prefix(); //Virtual prefix method

		this->m_window->events()->update(); //Poll Gl Events

		this->update(); //Update logic
		this->m_current_screen->update(Time::deltaTime()); // Update

		if (!this->m_window->isIconified())
		{
			this->m_current_screen->draw(Time::deltaTime()); // Draw
		}

		this->m_window->update(); //Swap buffer

		this->postfix(); //Virtual postfix method
	}
}

void EngineCoreApplication::loadAssets()
{
	try
	{
		std::shared_ptr<AssetsCoreLoader> core_asset_loader = std::make_shared<AssetsCoreLoader>(this->m_assets_manager);
		core_asset_loader->load();
	}
	catch (const std::exception& exc)
	{
		LOG(ERROR) << "Failed to load core assets, cause:\n\t" << exc.what();
		throw exc;
	}
	

	try
	{
		this->m_assets_loader.lock()->load();
	}
	catch (const std::exception& exc)
	{
		LOG(ERROR) << "Failed to load assets, cause:\n\t" << exc.what();
	}
}

void EngineCoreApplication::loadSystems()
{
	m_systems[SystemTypes::CONTROLLING] = std::make_shared<FreeFlySystem>();

	auto entity = m_registry.create();
	m_registry.emplace<Transform>(entity);
	m_registry.emplace<Camera>(entity, glm::vec3(0), this->m_global_settings->camera()->fov.get(), entity);
}

void EngineCoreApplication::update()
{
	for (const auto& system : this->m_systems)
	{
		system.second->update(this->m_registry);
	}
}

void EngineCoreApplication::prefix()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void EngineCoreApplication::postfix()
{
	this->m_window->clear();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}