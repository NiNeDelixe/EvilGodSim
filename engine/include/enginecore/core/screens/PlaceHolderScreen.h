#pragma once
#ifndef SCREENS_PLACEHOLDERSCREEN_H_
#define SCREENS_PLACEHOLDERSCREEN_H_

#include "enginecore/utils/ImguiIncludes.h"

#include "enginecore/core/screens/Screen.h"

#include "enginecore/core/EngineCoreApplication.h"

class PlaceHolderScreen : public Screen
{
public:
	PlaceHolderScreen() = default;
	~PlaceHolderScreen() = default;

public:
	void update(const float& delta) override;
	void draw(const float& delta) override;

private:

};


#endif // !SCREENS_PLACEHOLDERSCREEN_H_