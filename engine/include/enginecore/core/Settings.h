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
private:
	DECLARE_PRIVATE(EngineSettings);

public:
	AudioSettings& audio() { return d_ptr->audio; }
	CameraSettings& camera() { return d_ptr->camera; }
	ChunksSettings& chunks() { return d_ptr->chunks; }
	DebugSettings& debug() { return d_ptr->debug; }
	DisplaySettings& display() { return d_ptr->display; }
	GraphicsSettings& graphics() { return d_ptr->graphics; }
	NetworkSettings& network() { return d_ptr->network; }
	UiSettings& ui() { return d_ptr->ui; }

private:
	std::shared_ptr<EngineSettingsPrivate> d_ptr = std::make_shared<EngineSettingsPrivate>();
};


#endif // !TYPES_SETTINGS_H_