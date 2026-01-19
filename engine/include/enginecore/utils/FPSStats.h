#pragma once
#ifndef UTILS_FPSSTATS_H_
#define UTILS_FPSSTATS_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/core/Time.h"

class FPSCounter 
{    
public:
    FPSCounter()
    {
        m_fps_history.resize(HISTORY_SIZE, 0.0f);
        m_lastUpdateTime = Time::time();
    }

public:
    void update() 
    {
        ++m_frame_count;

        m_accumulatedTime += Time::deltaTime();

        if (Time::time() - m_last_fps_update_time >= 1.0) 
        {
            m_fps = static_cast<float>(m_frame_count) / 
                   static_cast<float>(Time::time() - m_last_fps_update_time);

            m_fps_history[m_historyIndex] = m_fps;
            m_historyIndex = (m_historyIndex + 1) % HISTORY_SIZE;
            
            recalculateStats();

            m_accumulatedTime = 0.0;
            m_frame_count = 0;
            m_last_fps_update_time = Time::time();
        }
    }

    void recalculateStats() {
        m_averageFPS = 0.0f;
        m_minFPS = FLT_MAX;
        m_maxFPS = 0.0f;
        
        int validSamples = 0;
        for (float fps : m_fps_history) {
            if (fps > 0.0f) {
                m_averageFPS += fps;
                m_minFPS = std::min(m_minFPS, fps);
                m_maxFPS = std::max(m_maxFPS, fps);
                ++validSamples;
            }
        }
        
        if (validSamples > 0) {
            m_averageFPS /= validSamples;
        }
    }
    
    float getFPS() const { return m_fps; }
    float getAverageFPS() const { return m_averageFPS; }
    float getMinFPS() const { return m_minFPS; }
    float getMaxFPS() const { return m_maxFPS; }
    const std::vector<float>& getHistory() const { return m_fps_history; }
    
    void reset() 
    {
        m_fps = 0.0f;
        m_frame_count = 0;
        m_last_fps_update_time = Time::time();
    }

private:
    float m_fps = 0.0f;
    int m_frame_count = 0;
    double m_last_fps_update_time = 0.0;

private:
    static constexpr int HISTORY_SIZE = 120;

    float m_averageFPS = 0.0f;
    float m_minFPS = FLT_MAX;
    float m_maxFPS = 0.0f;
    
    std::vector<float> m_fps_history;
    int m_historyIndex = 0;
    
    int m_frameCounter = 0;
    double m_accumulatedTime = 0.0;
    double m_lastUpdateTime = 0.0;
};

#endif  // UTILS_FPSSTATS_H_
