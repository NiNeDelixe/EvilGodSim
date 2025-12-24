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
    static inline void update(const double& current_time)
    {
        ++m_frame;
        m_delta = current_time - m_last_time;
        m_last_time = current_time;
    }

    static inline void step(const double& delta)
    {
        ++m_frame;
        m_last_time += delta;
        m_delta = delta;
    }

    static inline void set(const double& current_time)
    {
        m_last_time = current_time;
    }

    static inline const double& deltaTime()
    {
        return m_delta;
    }

    static inline const double& time()
    {
        return m_last_time;
    }

private:
    static inline uinteger_t m_frame = 0;
    static inline double m_last_time = 0.0;
    static inline double m_delta = 0.0;
};

#endif // !CORE_TIME_H_