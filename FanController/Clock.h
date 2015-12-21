#ifndef CLOCK_H
#define CLOCK_H

class Clock
{
public:
	Clock();
	void Update();
	int GetSeconds();
	int GetMinutes();
	int GetHours();
	int GetDays();
private:
	int m_Previous;
	int m_Current;
	int m_seconds;
	int m_minutes;
	int m_hours;
	int m_days;
	int m_CarryMS; //left over milliseconds
};

Clock::Clock()
{
	m_Previous = millis();
	m_seconds = 0;
	m_minutes = 0;
	m_hours = 0;
	m_days = 0;
}

void Clock::Update()
{
	m_Previous = m_Current;
	m_Current = millis();
	int DifferenceMS = (m_Current - m_Previous) + m_CarryMS;
	while (DifferenceMS >= 1000)
	{
		DifferenceMS -= 1000;
		m_seconds++;
	}
	m_CarryMS = DifferenceMS;
	
	while (m_seconds >= 60)
	{
		m_seconds -= 60;
		m_minutes++;
	}

	while (m_minutes >= 60)
	{
		m_minutes -= 60;
		m_hours++;
	}

	while (m_hours >=24)
	{
		m_hours -= 24;
		m_days++;
	}
}

int Clock::GetSeconds()
{
	return m_seconds;
}

int Clock::GetMinutes()
{
	return m_minutes;
}

int Clock::GetHours()
{
	return m_hours;
}

int Clock::GetDays()
{
	return m_days;
}
#endif
