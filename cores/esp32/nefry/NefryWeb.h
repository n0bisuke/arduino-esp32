#ifndef NefryWeb_h
#define NefryWeb_h


#include "Nefry.h"
#include "NefryDataStore.h"

class Nefry_Web
{
public:
	String
		beginWeb(String _viwePage),
		createHtml(String title, String head, String body);
};
extern Nefry_Web NefryWeb;
#endif
