#pragma once
#ifndef UTILS_TIMEUTILS_H_
#define UTILS_TIMEUTILS_H_

#include "enginecore/core/CoreDefines.h"
#include "enginecore/utils/platform/SystemDetection.h"

#ifdef E_OS_WIN
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#endif //E_OS_WIN

namespace UTILS_NAMESPACE
{
    namespace time
    {
        static inline void sleep(const size_t& millis)
        {
#ifdef E_OS_WIN
            static const UINT periodMin = [] {
                TIMECAPS tc;
                timeGetDevCaps(&tc, sizeof(TIMECAPS));
                return tc.wPeriodMin;
                }();

            timeBeginPeriod(periodMin);
            Sleep(static_cast<DWORD>(millis));
            timeEndPeriod(periodMin);
#else
            std::this_thread::sleep_for(std::chrono::milliseconds(millis));
#endif //E_OS_WIN
        }
    }
}

#endif // !UTILS_TIMEUTILS_H_