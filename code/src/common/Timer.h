#ifndef TIMER_H
#define TIMER_H
#include "define.h"
#include <vector>
#include <thread>
#include <memory>
#include <functional>
#include <chrono>

//typedef void(*CallBackFun)();
typedef std::function<void(void)> CallBackFun; 

namespace
{
    using chronotime_t = std::chrono::system_clock::time_point;
} // namespace

class Timer
{
public:
    Timer(/* args */);
    ~Timer();

    void start(uint32_t timeout,bool loop = false);
    void stop();
    void reStart(uint32_t timeout,bool loop = false);
    bool isStart();
    chronotime_t getStartTime();
    void setStartTime(chronotime_t starttime);
    uint32_t getTimeout();
    void runCallBack();
    void connect(CallBackFun callback);
    bool isLoop();
    CallBackFun getCallBack();
private:
    //void (*m_callback)();
    CallBackFun m_callback;
    bool m_start;
    uint32_t m_timeout;
    chronotime_t m_starttime;
    bool m_loop;
};

class TimerManager
{
public:
    static TimerManager &Instance(){static TimerManager m_instance; return m_instance;}
    ~TimerManager();

    void addTimer(Timer *pTimer);
    void delTimer(Timer *pTimer);
    void init();
    void task();
private:
    TimerManager(/* args */){};

    std::vector<Timer *> m_timerVector;
    std::shared_ptr<std::thread> m_thread;
};

#define sTimerManager TimerManager::Instance()

#endif