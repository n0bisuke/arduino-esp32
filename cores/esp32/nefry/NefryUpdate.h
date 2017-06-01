#ifndef NefryUpdate_h
#define NefryUpdate_h


#include "NefryWebServer.h"
#include "inc\Update\src\Update.h"
#include "Nefry.h"
#include "inc\ESP32httpUpdate\src\ESP32httpUpdate.h"


class Nefry_Update
{
public:
	void
		setupWebLocalUpdate(), 
		setupWebOnlineUpdate(), 
		setWebUpdate(String url, String domain);

	int autoUpdate(String url, String domain);

};
extern Nefry_Update NefryUpdate;
#endif
