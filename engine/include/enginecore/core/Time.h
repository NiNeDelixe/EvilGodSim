#pragma once
#ifndef CORE_TIME_H_
#define CORE_TIME_H_

#include <stdint.h>

#include "enginecore/core/CoreDefines.h"

class Time 
{
public:
    ~Time() = delete;

public:
    static inline void update(const etime_t& current_time)
    {
        ++m_frame;
        m_delta = current_time - m_last_time;
        m_last_time = current_time;
    }

    static inline void step(const etime_t& delta)
    {
        ++m_frame;
        m_last_time += delta;
        m_delta = delta;
    }

    static inline void set(const etime_t& current_time)
    {
        m_last_time = current_time;
    }

    static inline const etime_t& deltaTime()
    {
        return m_delta;
    }

    static inline const etime_t& time()
    {
        return m_last_time;
    }

    static inline const uinteger_t& frame()
    {
        return m_frame;
    }

private:
    static inline uinteger_t m_frame = 0;
    static inline etime_t m_last_time = 0.0;
    static inline etime_t m_delta = 0.0;
};

#endif // !CORE_TIME_H_