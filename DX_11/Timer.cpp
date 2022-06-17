#include "Timer.h"
using namespace std::chrono;

Timer::Timer() :m_StartTime(steady_clock::now()), m_LastTime(steady_clock::now())
{

}

float Timer::Mark()
{
	const auto oldTime = m_LastTime;
	m_LastTime = steady_clock::now();
	const duration<float> frameTime = m_LastTime - oldTime;
	return frameTime.count();
}

float Timer::Peek() const
{
	return duration<float>(steady_clock().now() - m_StartTime).count();
}
