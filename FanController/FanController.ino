/*
 Name:		FanController.ino
 Created:	12/20/2015 6:08:15 PM
 Author:	Steve
*/
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Timer.h"
#include "Clock.h"
#include "Potentiometer.h"
#include "Fan.h"
#include "LiquidCrystal595.h"

LiquidCrystal595 LCD(7, 8, 9);
Fan Fans[]{
	Fan(1,3),
	Fan(2,5),
	Fan(3,6),
	Fan(4,11),
	Fan(5,10),
};

Clock DaClock;
Timer ScrollTimer;
int FanIndex = 0;
bool FanBeingChanged = false;

void ClearLine(int StartColumn)
{
	LCD.setCursor(StartColumn, 0);
	for (int i = StartColumn; i < 16; i++)
		LCD.print(" ");
}

void setup() {
	LCD.begin(16, 2);
	LCD.setLED2Pin(HIGH);
	LCD.noAutoscroll();
	LCD.clear();
	ScrollTimer.SetWaitTime(3);
}

void loop() {
	for (int i = 0; i < 5; i++)
		Fans[i].Update();

	DaClock.Update();
	ScrollTimer.Update();
	//Rotate to next fan every 3 seconds
	if (ScrollTimer.IsReady() && !FanBeingChanged)
	{
		ScrollTimer.SetWaitTime(3);
		FanIndex++;
		if (FanIndex > 4)
			FanIndex = 0;
	}
	//Don't rotate if a fan is being changed
	if (FanBeingChanged)
		ScrollTimer.SetWaitTime(3);

	//Print Time
	char buffer[32];
	sprintf(buffer, "%d:%d:%d:%d", DaClock.GetDays(), DaClock.GetHours(), 
		DaClock.GetMinutes(), DaClock.GetSeconds());

	//Center it on bottom row
	LCD.setCursor(3, 1);
	LCD.print(buffer);
	int Length = strlen(buffer);
	ClearLine(Length + 3);

	//Bring fan being changed to focus
	FanBeingChanged = false;
	for (int i = 0; i < 5; i++)
	{
		if (Fans[i].HasChanged())
		{
			FanIndex = i;
			FanBeingChanged = true;
			break;
		}
	}

	//Print out stats for current fan
	char FanBuff[32];
	sprintf(FanBuff, "Fan %d %d%%", FanIndex+1, Fans[FanIndex].GetPercent());
	int FanLength = strlen(FanBuff);
	//Top Left
	LCD.setCursor(0, 0);
	LCD.print(FanBuff);
	ClearLine(FanLength);
}


