#pragma once
#ifndef ENGINE_ENGINECOREAPPLICATION_H_
#define ENGINE_ENGINECOREAPPLICATION_H_

#include <list>

#include <glog/logging.h>
#include <BS_thread_pool.hpp>
#include <entt/entt.hpp>

#include "enginecore/core/Time.h"
#include "enginecore/core/EnginePaths.h"

#include "enginecore/core/window/BaseWindow.h"
#include "enginecore/core/window/WindowEvents.h"

#include "enginecore/core/events/EventBus.h"

#include "enginecore/core/assets/AssetsCoreLoader.h"
#include "enginecore/core/assets/AssetsLoader.h"
#include "enginecore/core/assets/AssetsManager.h"

#include "enginecore/core/render/BaseRenderer.h"

#include "enginecore/core/screens/Screen.h"
#include "enginecore/core/screens/PlaceHolderScreen.h"

#include "enginecore/interfaces/ISystem.h"
#include "enginecore/interfaces/IEntity.h"

#include "enginecore/core/ecs/systems/CameraSystem.h"

#include "enginecore/utils/ImguiIncludes.h"

#ifdef ERROR
#undef ERROR
#endif // ERROR


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

public:
	void setScreen(const std::shared_ptr<Screen>& screen) { this->m_current_screen = screen; }

protected:
	BS::thread_pool m_thread_pool;

	bool m_in_exec = false;
	int m_return_code = 0;

	EVENT_NAMESPACE::EventBus m_events;

	std::weak_ptr<AssetsManager> m_assets_manager;
	std::weak_ptr<AssetsLoader> m_assets_loader;

	std::shared_ptr<BaseWindow> m_window = nullptr;
	std::shared_ptr<Screen> m_current_screen = nullptr;
	std::shared_ptr<EnginePaths> m_paths = nullptr;

	entt::basic_registry</*EntitySharedPointer<IEntity>*/> m_registry;
	std::list<std::shared_ptr<ISystem>> m_systems = {};

protected:
	static EngineCoreApplication* m_instance;
	ImGuiContext* m_gui_context = nullptr;
};

#endif // !ENGINE_ENGINECOREAPPLICATION_H_