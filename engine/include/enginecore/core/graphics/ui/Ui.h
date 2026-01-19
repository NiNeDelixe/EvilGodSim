#pragma once
#ifndef UI_UI_H_
#define UI_UI_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/utils/ImguiIncludes.h"

class Ui
{
public:
    Ui() {}
    virtual ~Ui() {}

public:
    virtual void update() = 0;
    virtual void render() = 0;
    
};

#endif  // UI_UI_H_
