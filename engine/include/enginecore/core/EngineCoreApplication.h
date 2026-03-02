#pragma once
#ifndef ENGINE_ENGINECOREAPPLICATION_H_
#define ENGINE_ENGINECOREAPPLICATION_H_

#include "enginecore/core/CoreDefines.h"

#include <list>
#include <deque>

#include <glog/logging.h>
#include <glm/ext.hpp>
#include <cpptrace/from_current.hpp>

#include "enginecore/core/LibrariesDefines.h"

#include "enginecore/core/Time.h"
#include "enginecore/core/EnginePaths.h"
#include "enginecore/core/Settings.h"

#include "enginecore/core/window/BaseWindow.h"
#include "enginecore/core/window/WindowEvents.h"

#include "enginecore/core/events/EventBus.h"

#include "enginecore/core/assets/loaders/IncludeLoaders.h"
#include "enginecore/core/assets/AssetsCoreLoader.h"
#include "enginecore/core/assets/AssetsLoader.h"
#include "enginecore/core/assets/AssetsManager.h"

#include "enginecore/core/graphics/render/BaseRenderer.h"
#include "enginecore/core/graphics/render/DrawContext.h"

#include "enginecore/core/screens/Screen.h"
#include "enginecore/core/screens/PlaceHolderScreen.h"

#include "enginecore/core/graphics/ui/Ui.h"
#include "enginecore/core/graphics/ui/DebugUi.h"

#include "enginecore/interfaces/ISystem.h"
#include "enginecore/interfaces/IEntity.h"

#include "enginecore/core/ecs/systems/managment/SystemsManager.h"
#include "enginecore/core/ecs/systems/managment/EngineSystemFactory.h"
#include "enginecore/core/ecs/entities/Camera.h"

#include "enginecore/core/lang/Localization.h"

#include "enginecore/utils/ImguiIncludes.h"
// #include "enginecore/utils/FPSStats.h"

// #ifdef ERROR
// #undef ERROR
// #endif // ERROR


class EngineCoreApplication;
#define EngiApp EngineCoreApplication::instance()

class EngineCoreApplication
{
public:
	EngineCoreApplication(int& argc, char** argv);

	EngineCoreApplication();
	virtual ~EngineCoreApplication();

public:
	int exec() noexcept(false);
	void quit(const int& return_code);

protected:
	void poll();

	void loadAssets();
	virtual void loadSystems();

	void update();

	/// @brief called when loop iteration start
	virtual void prefix();
	/// @brief called when loop iteration end
	virtual void postfix();

public:
	static EngineCoreApplication* instance() { return m_instance; }

	EVENT_NAMESPACE::EventBus& events() { return m_events; }

	const std::shared_ptr<BaseWindow>& window() const { return m_window; }
	const std::weak_ptr<AssetsManager>& assets() const { return m_assets_manager; }
	std::weak_ptr<EnginePaths> paths() const { return m_paths; }
	std::weak_ptr<DrawContext> ctx() const { return m_ctx; }
	const std::weak_ptr<AssetsLoader>& getAssetsLoader() const { return m_assets_loader; }
	// const std::weak_ptr<FPSCounter>& fpsStats() const { return m_fps_counter; }

public:
	GETTER(std::vector<std::shared_ptr<Ui>>, m_uis, Uis)
	SETTER(std::vector<std::shared_ptr<Ui>>, m_uis, Uis)

	GETTER(std::shared_ptr<SystemsManager>, m_systems_manager, SystemManager)
	SETTER(std::shared_ptr<SystemsManager>, m_systems_manager, SystemManager)

public:
	EntityRegistry<DefaultEntityIndentifier>& getEntityRegistry() { return this->m_registry; }
	// void setEntitySystem(const SystemCategory& type, const std::shared_ptr<ISystem>& system) { m_systems[type] = system; }
	// void addEntitySystem(const std::shared_ptr<ISystem>& system) { m_free_systems.push_back(system); }
	const EngineSettings::Ptr& getGlobalSettings() const { return this->m_global_settings; }

public:
	void setScreen(const std::shared_ptr<Screen>& screen) { this->m_current_screen = screen; }

protected:
	bool m_in_exec = false;
	int m_return_code = 0;

	EVENT_NAMESPACE::EventBus m_events;

	std::weak_ptr<AssetsManager> m_assets_manager;
	std::weak_ptr<AssetsLoader> m_assets_loader;

	std::shared_ptr<BaseWindow> m_window = nullptr;
	std::shared_ptr<Screen> m_current_screen = nullptr;
	std::vector<std::shared_ptr<Ui>> m_uis{};
	std::shared_ptr<EnginePaths> m_paths = nullptr;
	std::shared_ptr<DrawContext> m_ctx = nullptr;

	EntityRegistry<DefaultEntityIndentifier> m_registry;
	// std::unordered_map<SystemCategory, std::shared_ptr<ISystem>> m_systems = {};
	// std::vector<std::shared_ptr<ISystem>> m_free_systems = {};
	std::shared_ptr<SystemsManager> m_systems_manager;

	EngineSettings::Ptr m_global_settings;

protected:
	static EngineCoreApplication* m_instance;
	ImGuiContext* m_gui_context = nullptr;
};

#endif // !ENGINE_ENGINECOREAPPLICATION_H_