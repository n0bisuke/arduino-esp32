#ifndef Nefry_h
#define Nefry_h

#include <Esp.h>
#include "./inc/led/Adafruit_NeoPixel.h"
#include "./inc/Preferences/src/Preferences.h"
//#include "NefryWebServer.h"
#include "NefryWiFi.h"
#include "./NefryDataStore.h"
#include "NefryConfig.h"
#include "NefryConsole.h"

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
		setStoreValue(long value, int pointer),
		setStoreStr(String str, int pointer),
		getWriteMode(),
		readSW(),
		getPollingSW();

	String
		getModuleID(),
		getModuleClass(),
		getUser(),
		getStoreStr(int pointer),
		getVersion(),
		getProgramName(),
		getAddressStr(IPAddress ip),
		getDefaultModuleId(),
		/* Console */
		read();

	long
		getStoreValue(int pointer),
		getBootMode();

	int
		/* Console */
		available(),
		getNefryState();
	void
		reset(),
		sleep(const int sec),
		setProgramName(const char * pn),
		beginLed(const int num, const int pin, uint8_t t),
		setLed(const int r, const int g, const int b, const char w = 122, const int pin = 16, const int num = 0),
		setLed(String _colorStr, const char w = 122, const int pin = 16, const int num = 0),
		addWiFi(String ssid, String pass),
		deleteWiFi(int id),
		saveWiFi(),
		nefry_init(),
		nefry_loop(),
		ndelay(unsigned long ms),

		setStoreTitle(const char set[15], const int num),

		enableSW(),
		disableSW(),

		/* Pollingでスイッチの状態をチェック */
		pollingSW(),

		/* Console機能追加 */
		clearConsole(),

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
		print(String text),
		println(String text),

		setNefryState(int state);

private:
	bool
		_swEnableFlg = false,/* SWの有効無効化 */
		_swflg = false, /* SWの状態を保持 */
		_swPushingflg = false;

	int 
		_bootMode = -1,	/* Boot状態を管理　-1:初期化中 0:起動中 1:通常起動 2:書き込みモード */
		hextonum(char c),
		_nefryState = 0;
	
	const char * program;
};
extern Nefry_lib Nefry;
#endif