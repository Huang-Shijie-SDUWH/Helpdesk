/*接线
 * ST7920/LCD12864---arduino uno
 * VCC-------------5V
 * GND-------------GND
 * PSB----------------GND//低电平使用并口
 * E------------------18
 * R/W----------------23
 * R/S----------------5
 * RST----------------22
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include <Button2.h>
#include <EasyBuzzer.h>
#include <WiFi.h>
#include <WebSocketClient.h>

#define WIFI_SSID "1712W24"	 // change with your own wifi ssid
#define WIFI_PASS "88883333" // change with your own wifi password

#ifdef U8X8_HAVE_HW_SPI //SPI通讯
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_ST7920_128X64_2_SW_SPI u8g2(U8G2_R0, /* E=*/18, /* RW=*/23, /* RS=*/5, /* RST=*/22); // ESP32

#define BUTTON_A_PIN 13
#define BUTTON_B_PIN 12
#define BUTTON_C_PIN 14
#define BUTTON_D_PIN 27
Button2 buttonA, buttonB, buttonC, buttonD;
WiFiClient client;
int beep = 33;
char *message = "欢迎使用求助机";

char connect()
{
	WiFi.begin(WIFI_SSID, WIFI_PASS);

	Serial.println("Waiting for wifi");
	int timeout_s = 30;
	while (WiFi.status() != WL_CONNECTED && timeout_s-- > 0)
	{
		delay(1000);
		Serial.print(".");
	}

	if (WiFi.status() != WL_CONNECTED)
	{
		Serial.println("无法连接，请检查密码");
		return 0;
	}
	else
	{
		Serial.println("WIFI连接成功！");
		Serial.println(WiFi.localIP());
		return 1;
	}
}
void ez_beep(int time)
{
	if (time < 1)
		return;
	if (time == 1)
	{
		EasyBuzzer.singleBeep(
			1000, // Frequency in hertz(HZ).
			1000  // Duration of the beep in milliseconds(ms).
		);
	}
	else
	{
		EasyBuzzer.beep(
			1000,	  // Frequency in hertz(HZ).
			1000,	  // On Duration in milliseconds(ms).
			1000,	  // Off Duration in milliseconds(ms).
			time - 1, // The number of beeps per cycle.
			1000,	  // Pause duration.
			1		  // The number of cycle.
		);
	}
}
void click(Button2 &btn)
{
	if (btn == buttonA)
	{
		Serial.println("A clicked");
		message = "我生病了";
		ez_beep(1);
	}
	if (btn == buttonB)
	{
		Serial.println("B clicked");
		message = "失火了";
		ez_beep(1);
	}
	if (btn == buttonC)
	{
		Serial.println("C clicked");
		message = "电路故障";
		ez_beep(1);
	}
	if (btn == buttonD)
	{
		Serial.println("D clicked");
		message = "其他求助";
		ez_beep(1);
	}
}

void setup(void)
{
	Serial.begin(115200);
    // 尝试连接WIFI
    if (connect() == 0)
    {
        return;
    }
	u8g2.begin();
	u8g2.enableUTF8Print();						// enable UTF8 support for the Arduino print() function
	u8g2.setFont(u8g2_font_unifont_t_chinese2); // use chinese2 for all the glyphs of "你好世界"
	u8g2.setFontDirection(0);
	EasyBuzzer.setPin(beep);
	ez_beep(3);

	buttonA.begin(BUTTON_A_PIN);
	buttonA.setClickHandler(click);
	buttonB.begin(BUTTON_B_PIN);
	buttonB.setClickHandler(click);
	buttonC.begin(BUTTON_C_PIN);
	buttonC.setClickHandler(click);
	buttonD.begin(BUTTON_D_PIN);
	buttonD.setClickHandler(click);
}

void loop(void)
{
	u8g2.firstPage();
	u8g2.setCursor(0, 15);
	u8g2.print(message);
	buttonA.loop();
	buttonB.loop();
	buttonC.loop();
	buttonD.loop();
	EasyBuzzer.update();
}
