#ifndef NefryUpdate_h
#define NefryUpdate_h


#include "NefryWebServer.h"
#include "inc/Update/src/Update.h"
#include "Nefry.h"


class Nefry_Update
{
public:
	void
		setupWebOnlineUpdate(void),
		setupWebLocalUpdate(),
		beginWeb();
	int setUpdateWeb(String host,String url);
	String getHeaderValue(String header, String headerName);

private:
	int contentLength = 0;
	bool isValidContentType = false;
};
extern Nefry_Update NefryUpdate;
#endif
