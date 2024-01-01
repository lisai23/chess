#include <vector>
#include <chrono>
#include <algorithm>
#include <unistd.h>
#include <mutex>
#include "Timer.h"

std::mutex g_timer_mutex;

Timer::Timer() :
	m_timeout(0),
	m_loop(false),
	m_start(false),
	m_callback(nullptr)
{
	g_timer_mutex.lock();
	sTimerManager.addTimer(this);
	g_timer_mutex.unlock();
}
Timer::~Timer()
{
	g_timer_mutex.lock();
	sTimerManager.delTimer(this);
	g_timer_mutex.unlock();
}

void Timer::connect(CallBackFun callback)
{
	m_callback = std::move(callback);
}

void Timer::start(uint32_t timeout,bool loop)
{
	g_timer_mutex.lock();
	m_timeout = timeout;
	m_loop = loop;
	m_start = true;
	m_starttime = std::chrono::system_clock::now();
	g_timer_mutex.unlock();
}
void Timer::stop()
{
	g_timer_mutex.lock();
	m_start = false;
	g_timer_mutex.unlock();
}
void Timer::reStart(uint32_t timeout,bool loop)
{
	start(timeout, loop);
}

bool Timer::isStart()
{
	return m_start;
}

bool Timer::isLoop()
{
	return m_loop;
}

uint32_t Timer::getTimeout()
{
	return m_timeout;
}

chronotime_t Timer::getStartTime()
{
	return m_starttime;
}

void Timer::setStartTime(chronotime_t starttime)
{
	m_starttime = starttime;
}

CallBackFun Timer::getCallBack()
{
	return m_callback;
}

void Timer::runCallBack()
{
	if (nullptr != m_callback)
	{
		m_callback();
	}
}

TimerManager::~TimerManager()
{
	
}

void TimerManager::init()
{
	m_thread = std::make_shared<std::thread>(&TimerManager::task,this);
	m_thread->detach();
}
void TimerManager::task()
{
	while (true)
	{
		g_timer_mutex.lock();
		const chronotime_t now = std::chrono::system_clock::now();
		for (auto t: m_timerVector)
		{
			if(t && t->isStart() && t->getCallBack())
			{
				const auto diff = now - t->getStartTime();
				const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
				if (msec.count() >= static_cast<int64_t>(t->getTimeout()))
				{
					if (t->isLoop())
					{
						t->setStartTime(std::chrono::system_clock::now());
					}
					else
					{
						g_timer_mutex.unlock();
						t->stop();
						g_timer_mutex.lock();
					}
					/*callback function maybe start or stop timer, lock will double*/
					g_timer_mutex.unlock();
					t->runCallBack();
					g_timer_mutex.lock();
				}
			}
		}
		g_timer_mutex.unlock();
		usleep(5000);
	}
}

void TimerManager::addTimer(Timer *pTimer)
{
	m_timerVector.push_back(pTimer);
}

void TimerManager::delTimer(Timer *pTimer)
{
	auto p = find(begin(m_timerVector), end(m_timerVector), pTimer);
	m_timerVector.erase(p);
}