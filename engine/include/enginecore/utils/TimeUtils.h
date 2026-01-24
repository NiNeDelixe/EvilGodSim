#pragma once
#ifndef UTILS_TIMEUTILS_H_
#define UTILS_TIMEUTILS_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/utils/platform/SystemDetection.h"

#if defined(E_OS_WIN) && defined(ENGINE_USE_WINDOWS_HEADER)
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#else
#include <thread>
#endif //E_OS_WIN

namespace UTILS_NAMESPACE
{
    namespace time
    {
        static inline void sleep(const size_t& millis)
        {
#if defined(E_OS_WIN) && defined(ENGINE_USE_WINDOWS_HEADER)
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