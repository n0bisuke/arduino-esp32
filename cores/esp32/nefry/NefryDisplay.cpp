#include "NefryDisplay.h"

//SSD1306  display(0x3c, , D5);
SSD1306  display(0x3c, SDA, SCL);


/* 初期化 */
bool Nefry_Display::begin()
{
	// Initialising the UI will init the display too.
	display.init();
	display.flipScreenVertically();
	display.setContrast(255);

	//display.flipScreenVertically();
	//display.setFont(ArialMT_Plain_10);

	return true;
}

/* 表示 */
bool Nefry_Display::print(String s)
{
	display.clear();
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_10);
	display.drawString(0, 0, "Hello world");
	display.setFont(ArialMT_Plain_16);
	display.drawString(0, 10, "Hello world");
	display.setFont(ArialMT_Plain_24);
	display.drawString(0, 26, "Hello world");
	display.display();
	return true;
}
Nefry_Display NefryDisplay;
