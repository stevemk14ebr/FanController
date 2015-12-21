#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer
{
public:
	Potentiometer(int Pin);
	int GetCurrentValue();
	bool HasChanged();
private:
	void UpdateValue();
	int m_Pin;
	int m_CurrentValue;
	bool m_HasChanged;
};

Potentiometer::Potentiometer(int Pin)
{
	m_Pin = Pin;
	pinMode(m_Pin, OUTPUT);
	UpdateValue();
	m_HasChanged = false;
}

void Potentiometer::UpdateValue()
{
	int PreviousValue = m_CurrentValue;
	m_CurrentValue = analogRead(m_Pin);
	int Delta = abs(PreviousValue - m_CurrentValue);
	if (Delta > 5)
		m_HasChanged = true;
	else
		m_HasChanged = false;
}

int Potentiometer::GetCurrentValue()
{
	UpdateValue();
	return m_CurrentValue;
}

bool Potentiometer::HasChanged()
{
	return m_HasChanged;
}
#endif
