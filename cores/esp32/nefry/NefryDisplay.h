#ifndef NefryDisplay_h
#define NefryDisplay_h
#include <Arduino.h>
#include "inc\ssd1306\SSD1306.h"


class Nefry_Display
{
public:
	
	bool 
		begin(),
		print(String s);

};
extern Nefry_Display NefryDisplay;
#endif