#ifndef TIMER_H
#define TIMER_H
class Timer
{
public:
	Timer();
	void Update();
	void SetWaitTime(int Seconds);
	bool IsReady();
private:
	int m_Previous;
	int m_Current;
	int m_Seconds;
	int m_CarryMS; //left over milliseconds
	int m_DesiredTime;
	bool m_TimePassed;
};

Timer::Timer()
{
	m_Previous = millis();
	m_TimePassed = false;
	m_Seconds = 0;
}

void Timer::Update()
{
	m_Previous = m_Current;
	m_Current = millis();
	int DifferenceMS = (m_Current - m_Previous) + m_CarryMS;
	while (DifferenceMS >= 1000)
	{
		DifferenceMS -= 1000;
		m_Seconds++;
	}
	m_CarryMS = DifferenceMS;

	if (m_Seconds >= m_DesiredTime)
		m_TimePassed = true;
	else
		m_TimePassed = false;
}

bool Timer::IsReady()
{
	return m_TimePassed;
}

void Timer::SetWaitTime(int Seconds)
{
	m_DesiredTime = Seconds;
	m_Seconds = 0;
	m_Current = millis();
}
#endif
