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
	do {
		static const uint8_t data[] PROGMEM = {
			// Character#0
			0b01110,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b01110,
			// Character#1
			0b00000,
			0b01110,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b01110,
			// Character#2
			0b00000,
			0b00000,
			0b01110,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b01110,
			// Character#3
			0b00000,
			0b00000,
			0b00000,
			0b01110,
			0b10001,
			0b10001,
			0b10001,
			0b01110,
			// Character#4
			0b00000,
			0b00000,
			0b00000,
			0b00000,
			0b01110,
			0b10001,
			0b10001,
			0b01110,
			// Character#5
			0b00000,
			0b00000,
			0b00000,
			0b01110,
			0b10001,
			0b10001,
			0b01110,
			0b00000,
			// Character#6
			0b00000,
			0b00000,
			0b01110,
			0b10001,
			0b10001,
			0b01110,
			0b00000,
			0b00000,
			// Character#7
			0b00000,
			0b01110,
			0b10001,
			0b10001,
			0b01110,
			0b00000,
			0b00000,
			0b00000,
		};
		lcd.WriteCGRAM_P(0, data, sizeof(data));
	} while (0);
}

uint8_t codeTop = 0;

void loop()
{
	if (alarm.IsExpired()) {
		lcd.SetPosition(0, 0);
		lcd.Printf("Character %02X-%02X", codeTop, codeTop + 15);
		lcd.SetPosition(0, 1);
		for (uint8_t i = 0; i < 16; i++) {
			lcd.PutChar(codeTop + i);
		}
		codeTop += 16;
		alarm.Start();
	}
}
