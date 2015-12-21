// Fan.h

#ifndef FAN_H
#define FAN_H

class Fan
{
public:
	Fan(int KnobPin, int FanPin);
	void Update();
	int GetPercent();
	bool HasChanged();
private:
	void WriteSpeed(int Value);
	Potentiometer m_Knob;
	int m_Pin;
	int m_Percent;
	int m_CurrentSpeed;
	int m_MinSpeed;
	int m_MaxSpeed;
};

Fan::Fan(int KnobPin, int FanPin) : m_Knob(KnobPin)
{
	m_Pin = FanPin;
	m_MinSpeed = 0;
	m_MaxSpeed = 255;
	pinMode(m_Pin, INPUT);
}

void Fan::Update()
{
	int KnobValue = m_Knob.GetCurrentValue();
	m_CurrentSpeed = map(KnobValue, 0, 1024, m_MinSpeed, m_MaxSpeed);
	m_Percent = map(KnobValue,0, 1024, 0, 100);
	WriteSpeed(m_CurrentSpeed);
}

void Fan::WriteSpeed(int Value)
{
	analogWrite(m_Pin, Value);
}

int Fan::GetPercent()
{
	return m_Percent;
}

bool Fan::HasChanged()
{
	return m_Knob.HasChanged();
}
#endif

