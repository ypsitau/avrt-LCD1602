#include <avrt.h>
#include <avrt-LCD1602_TWI.h>

namespace av = avrt;

AVRT_IMPLEMENT_Timer1(timer)
AVRT_IMPLEMENT_TwoWire(twi, timer)
AVRT_IMPLEMENT_Serial0_NoRecv(serial)

av::LCD1602_TWI lcd(twi);

av::Timer::Alarm alarm(timer);

void setup()
{
	timer.Start();
	serial.Open(serial.Speed::Bps57600);
	twi.Open();
	lcd.Open();
	lcd.Clear();
	lcd.EntryModeSet(true, false);
	lcd.DisplayOnOffControl(true, false, false);
	lcd.FunctionSet(true, true);
	lcd.Printf(F("LCD1602 Test"));
	alarm.Start(1000);
}

int cnt = 0;

void loop()
{
	if (alarm.IsExpired()) {
		if (cnt == 0) lcd.Clear();
		lcd.SetPosition(0, 0);
		lcd.Printf(F("Count:%4d"), cnt);
		cnt++;
		alarm.Start();
	}
}
