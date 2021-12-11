#include <Arduino.h>
#include <U8g2lib.h>
#include <Button2.h>
#include <EasyBuzzer.h>

#ifdef U8X8_HAVE_HW_SPI//SPI通讯
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/18, /* data=*/23, /* CS=*/5, /* reset=*/22); // ESP32

#define BUTTON_A_PIN 13
#define BUTTON_B_PIN 12
#define BUTTON_C_PIN 14
#define BUTTON_D_PIN 27
Button2 buttonA, buttonB, buttonC, buttonD;

void done() {
	Serial.println("Done!");
}
unsigned int frequency = 1000;
unsigned int duration = 1000;
int beep = 19;
void click(Button2 &btn)
{
	if (btn == buttonA)
	{
		Serial.println("A clicked");
	}
	if (btn == buttonB)
	{
		Serial.println("B clicked");
	}
	if (btn == buttonC)
	{
		Serial.println("C clicked");
	}
	if (btn == buttonD)
	{
		Serial.println("D clicked");
	}
}
void setup(void)
{
    Serial.begin(115200);
	u8g2.begin();
	u8g2.enableUTF8Print(); // enable UTF8 support for the Arduino print() function
	delay(5000);
	// EasyBuzzer.setPin(beep);
	// EasyBuzzer.beep(
	// 	1000,		// Frequency in hertz(HZ).
	// 	1000, 		// On Duration in milliseconds(ms).
	// 	1000, 		// Off Duration in milliseconds(ms).
	// 	2, 		// The number of beeps per cycle.
	// 	1000, 	// Pause duration.
	// 	1, 		// The number of cycle.
	// 	done		// [Optional] Function to call when done.
	// );
	// Serial.println("\n\nMultiple Buttons Demo");

	// buttonA.begin(BUTTON_A_PIN);
	// buttonA.setClickHandler(click);
	// buttonB.begin(BUTTON_B_PIN);
	// buttonB.setClickHandler(click);
	// buttonC.begin(BUTTON_C_PIN);
	// buttonC.setClickHandler(click);
	// buttonD.begin(BUTTON_D_PIN);
	// buttonD.setClickHandler(click);
}

void loop(void)
{
	u8g2.setFont(u8g2_font_unifont_t_chinese2); // use chinese2 for all the glyphs of "你好世界"
	u8g2.setFontDirection(0);
	do
	{
		u8g2.setCursor(0, 15);
		u8g2.print("Hello World!");
		u8g2.setCursor(0, 40);
		u8g2.print("世界你好");
	} while (u8g2.nextPage());
	delay(1000);
	// buttonA.loop();
	// buttonB.loop();
	// buttonC.loop();
	// buttonD.loop();
	// EasyBuzzer.update();
}
