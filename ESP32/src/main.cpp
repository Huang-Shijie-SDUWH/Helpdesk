/*接线
 * SSD1309/OLED128X64---NODE MCU32/arduino iic
 * OLED VCC----------------3.3v
 * GND---------------------GND
 * OLED SCL----------------5
 * OLED SDA----------------23
 * Other-------------------NODE MCU32/arduino iic
 * Beep--------------------19
 * BUTTON_A----------------12
 * BUTTON_B----------------14
 * BUTTON_C----------------27
 * BUTTON_D----------------26
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

U8G2_SSD1309_128X64_NONAME2_2_SW_I2C u8g2(U8G2_R0, /* SCL=*/ 5, /* SDA=*/ 18, /* RST=*/ U8X8_PIN_NONE);

#define BUTTON_A_PIN 12
#define BUTTON_B_PIN 14
#define BUTTON_C_PIN 27
#define BUTTON_D_PIN 26
Button2 buttonA, buttonB, buttonC, buttonD;
WiFiClient client;
int beep = 19;
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
    message = "无法连接，请检查密码";
		return 0;
	}
	else
	{
		Serial.println("WIFI连接成功！");
    message = "WIFI连接成功！";
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
			time, // The number of beeps per cycle.
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
	u8g2.begin();
	u8g2.enableUTF8Print();
	u8g2.setFont(u8g2_font_wqy12_t_gb2312);
	u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print(message);
  u8g2.sendBuffer();
    // 尝试连接WIFI
  connect();
	EasyBuzzer.setPin(beep);
	ez_beep(3);
	Serial.begin(115200);

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
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print(message);
  u8g2.sendBuffer();
	buttonA.loop();
	buttonB.loop();
	buttonC.loop();
	buttonD.loop();
	EasyBuzzer.update();
}
