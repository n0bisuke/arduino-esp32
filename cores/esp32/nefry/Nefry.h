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
		setStorageStr(String str, int pointer),
		getBootFlg(),
		readSW();

	String
		getModuleID(),
		getModuleClass(),
		getUser(),
		getStorageStr(int pointer),
		getVersion(),
		getProgramName(),
		getAddressStr(IPAddress ip);

	long
		getStorageValue(int pointer);


	void
		reset(),
		sleep(const int sec),
		setProgramName(const char * pn),
		beginLed(const int num, const int pin, uint8_t t),
		setLed(const int r, const int g, const int b, const char w = 122, const int pin = 16, const int num = 0),
		setLed(String _colorStr, const char w = 122, const int pin = 16, const int num = 0),
		addWiFi(String ssid,String pass),
		deleteWiFi(int id),
		saveWiFi(),
		nefry_init(),
		nefry_loop(),
		ndelay(unsigned long ms),

		enableSW(),
		disableSW(),

	/* Pollingでスイッチの状態をチェック */
		pollingSW();

private:
	bool 
		_swEnableFlg,
		_bootMode = true,
		_swflg = false;

	int hextonum(char c);
	
};
extern Nefry_lib Nefry;
#endif