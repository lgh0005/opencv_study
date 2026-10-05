#include "pch.h"
#include "CVProfiler.h"

#ifdef _DEBUG
void CVProfiler::Start()
{
	m_timer.reset();
	m_timer.start();
	m_running = true;
}

double CVProfiler::Stop()
{
	if (m_running)
	{
		m_timer.stop();
		m_running = false;
	}

	return m_timer.getTimeMilli();
}

void CVProfiler::Reset()
{
	m_timer.reset();
	m_running = false;
}

double CVProfiler::GetElapsedMilliseconds() const
{
	return m_timer.getTimeMilli();
}
#endif
