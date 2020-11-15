#include "Timer.h"


Timer::Timer() : m_timeLeft(0.)
               , m_isRunning(false)
{
}

void Timer::start(double duration)
{
    if(m_isRunning)
        return;
    m_timeLeft = duration;
    m_isRunning = true;
}

void Timer::update(double delta)
{
    if (!m_isRunning)
        return;
    m_timeLeft -= delta;
    if (m_timeLeft <= 0)
    {
        m_isRunning = false;
        m_callBack();
    }
}
