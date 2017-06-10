#ifndef NefryDisplay_h
#define NefryDisplay_h

#include <Wire.h> 
#include "inc/ssd1306/SSD1306.h"

class Nefry_Display
{
public:
	void
		begin(),
		
		println(float text),
		println(double text),
		println(char text),
		println(int text),
		println(long text),
		println(unsigned char text),
		println(unsigned int text),
		println(unsigned long text),
		print(float text),
		print(double text),
		print(char text),
		print(int text),
		print(long text),
		print(unsigned char text),
		print(unsigned int text),
		print(unsigned long text),
		print(String text, int ln = 0),
		println(String text);



private:
};
extern Nefry_Display NefryDisplay;
#endif
