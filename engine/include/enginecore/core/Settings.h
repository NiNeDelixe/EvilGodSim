#pragma once
#ifndef TYPES_SETTINGS_H_
#define TYPES_SETTINGS_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "enginecore/core/CoreDefines.h"

#include "enginecore/utils/types/Setting.h"

#include "Settings_p.h"

class EngineSettings 
{
public:
	DECLARE_PTR(EngineSettings)

public:
	const std::shared_ptr<AudioSettings>& audio() const{ return d_ptr->audio; }
	const std::shared_ptr<CameraSettings>& camera() const { return d_ptr->camera; }
	const std::shared_ptr<ChunksSettings>& chunks() const { return d_ptr->chunks; }
	const std::shared_ptr<DebugSettings>& debug() const { return d_ptr->debug; }
	const std::shared_ptr<DisplaySettings>& display() const { return d_ptr->display; }
	const std::shared_ptr<GraphicsSettings>& graphics() const { return d_ptr->graphics; }
	const std::shared_ptr<NetworkSettings>& network() const { return d_ptr->network; }
	const std::shared_ptr<UiSettings>& ui() const { return d_ptr->ui; }

private:
	std::shared_ptr<EngineSettingsPrivate> d_ptr = std::make_shared<EngineSettingsPrivate>();
};


#endif // !TYPES_SETTINGS_H_