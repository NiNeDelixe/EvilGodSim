#pragma once
#ifndef INTERFACES_IEVENT_H_
#define INTERFACES_IEVENT_H_

#include "enginecore/core/CoreDefines.h"

namespace EVENT_NAMESPACE
{
    struct IEvent
    {
        virtual ~IEvent() = default;
    };
}

#endif // !INTERFACES_IEVENT_H_