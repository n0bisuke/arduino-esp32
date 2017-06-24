#ifndef NefryDisplay_h
#define NefryDisplay_h
#include <Arduino.h>

class Nefry_Display
{
public:
	
	bool 
		begin(),
		print(String s);

};
extern Nefry_Display NefryDisplay;
#endif