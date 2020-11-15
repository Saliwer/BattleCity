#pragma once
#include <functional>

class Timer{
public:

    Timer();
    // TODO - template function
    void setCallBack(std::function<void()> callBackFunc){ m_callBack = callBackFunc; }
    void start(double duration);
    void update(double delta);

private:
    std::function<void()>   m_callBack;
    double                  m_timeLeft;
    bool                    m_isRunning;
};
