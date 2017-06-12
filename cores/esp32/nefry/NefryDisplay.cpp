/**
Nefry lib

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "NefryDisplay.h"
SSD1306  display(0x3c, SDA, SCL);
//webConsole

void Nefry_Display::println(float text) { println(String(text)); }
void Nefry_Display::println(double text) { println(String(text)); }
void Nefry_Display::println(char text) { println(String(text)); }
void Nefry_Display::println(int text) { println(String(text)); }
void Nefry_Display::println(long text) { println(String(text)); }
void Nefry_Display::println(unsigned char text) { println(String(text)); }
void Nefry_Display::println(unsigned int text) { println(String(text)); }
void Nefry_Display::println(unsigned long text) { println(String(text)); }
void Nefry_Display::print(float text) { print(String(text)); }
void Nefry_Display::print(double text) { print(String(text)); }
void Nefry_Display::print(char text) { print(String(text)); }
void Nefry_Display::print(int text) { print(String(text)); }
void Nefry_Display::print(long text) { print(String(text)); }
void Nefry_Display::print(unsigned char text) { print(String(text)); }
void Nefry_Display::print(unsigned int text) { print(String(text)); }
void Nefry_Display::print(unsigned long text) { print(String(text)); }
int printcun;
#define max_console 30
char printweb[max_console][50];
int mojicount = 0;
void Nefry_Display::print(String text, int ln) {
	if (printcun >= max_console)printcun = 0;
	Serial.print(text);
	if (ln == 1)text += "<br>";
	text.toCharArray(printweb[printcun++], 50);
	if (mojicount <= max_console)mojicount++;
}

void Nefry_Display::println(String text) {
	print(text, 1);
	Serial.println();
}

void Nefry_Display::begin() {

}
Nefry_Display NefryDisplay;