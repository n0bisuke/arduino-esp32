#ifndef Nefry_h
#define Nefry_h

#include <Esp.h>
#include "./inc/led/Adafruit_NeoPixel.h"
#include "./inc/Preferences/src/Preferences.h"
//#include "NefryWebServer.h"
#include "NefryWiFi.h"
#include "./NefryDataStore.h"

// Offset:         W          R          G          B
#define NEO_RGB  ((0 << 6) | (0 << 4) | (1 << 2) | (2))
#define NEO_RBG  ((0 << 6) | (0 << 4) | (2 << 2) | (1))
#define NEO_GRB  ((1 << 6) | (1 << 4) | (0 << 2) | (2))
#define NEO_GBR  ((2 << 6) | (2 << 4) | (0 << 2) | (1))
#define NEO_BRG  ((1 << 6) | (1 << 4) | (2 << 2) | (0))
#define NEO_BGR  ((2 << 6) | (2 << 4) | (1 << 2) | (0))


class Nefry_lib
{
public:

	bool
		setModuleID(String id),
		setModulePass(String pass),
		setModuleClass(String className),
		setUser(String user),
		setUserPass(String pass),
		setStorageValue(long value, int pointer),
		setStorageStr(String str, int pointer);

	String
		getModuleID(),
		getModuleClass(),
		getUser(),
		getStorageStr(int pointer);

	long
		getStorageValue(int pointer);


	void
		reset(),
		sleep(const int sec),
		setProgramName(const char * pn),
		setIndexLink(const char title[32], const char url[32]),
		beginLed(const int num, const int pin, uint8_t t),
		setLed(const int r, const int g, const int b, const char w = 122, const int pin = 16, const int num = 0),
		setLed(String _colorStr, const char w = 122, const int pin = 16, const int num = 0),
/*
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
		println(String text),
		*/
		nefry_init(),
		nefry_loop(),
		ndelay(unsigned long ms);

	void enableSW();

	void disableSW();

	bool
		readSW(),
		autoConnect(),
		getConfHtmlPrint(const int num),
		setConfValue(const int pt, const int num),
		setConfStr(const char *pt, const int num),
		login(const char *UserID, const char *User_pass),
		Auth(const char *Nefryclass, const char *NefryID),
		getWifiAuto(), 
		push_sw_();

	void pollingSW();
	bool getBootFlg();
	char* getConfStr(const int num);


	String read(),
		getVersion(),
		getProgramName(),
		getAddressStr(IPAddress ip),
		getModuleWiFiPass();


private:
	bool _swEnableFlg;
	bool _bootMode = true, _swflg = false;
	int hextonum(char c);
	
};
extern Nefry_lib Nefry;
#endif

void _swcallback_function();
