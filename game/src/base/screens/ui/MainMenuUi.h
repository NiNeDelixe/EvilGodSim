#pragma once
#ifndef UI_MAINMENUUI_H_
#define UI_MAINMENUUI_H_

#include <enginecore/core/graphics/ui/Ui.h>

#include <enginecore/core/EngineCoreApplication.h>

#include <enginecore/utils/ImguiIncludes.h>

#include "base/screens/GameScreen.h"

class MainMenuUi : public Ui
{
public:
    MainMenuUi() {}
    ~MainMenuUi() {}

public:
    virtual void update() override;
    virtual void render() override;

private:
};

#endif  // UI_MAINMENUUI_H_
