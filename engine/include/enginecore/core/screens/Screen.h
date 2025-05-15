#pragma once
#ifndef SCREENS_SCREEN_H_
#define SCREENS_SCREEN_H_

#include "enginecore/utils/ObjectsKeeper.h"

/// @brief Screen is a mainloop state
class Screen : public UTILS_NAMESPACE::memory::ObjectsKeeper
{
public:
    Screen() = default;
    virtual ~Screen() = default;
    virtual void update(const float& delta) = 0;
    virtual void draw(const float& delta) = 0;
    virtual void onEngineShutdown() {};

protected:
    //std::shared_ptr<Batch2D> batch;
};

#endif // !SCREENS_SCREEN_H_