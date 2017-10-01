#ifndef NefryThingSpeak_h
#define NefryThingSpeak_h

#include <include/src/ThingSpeak.h>
#include <Nefry.h>

class NefryThingSpeakClass:public ThingSpeakClass
{
public:
	void begin(int nefryConfigChannelNumber = 0, const char* hint = "ChannelNum");
	void setWriteAPIKey(int nefryConfigWriteApikey = 0, const char* hint = "WriteKey");
	void setReadAPIKey(int nefryConfigReadApikey = 1, const char* hint = "ReadKey");
	const char * getWriteAPIKey();
	const char * getReadAPIKey();
	unsigned long getChannelNumber();
	int writeField(unsigned int field, int value );
	int writeField(unsigned int field, long value );
	int writeField(unsigned int field, float value );
	int writeField(unsigned int field, const char *  value );
	int writeField(unsigned int field, String  value );
	int writeFields();

private:
	WiFiClient  _nefryThingClient;
	int _nefryConfigChannelNumber, _nefryConfigWriteApikey, _nefryConfigReadApikey;
	String _nefryWriteAPIKey, _nefryReadAPIKey;
};
extern NefryThingSpeakClass NefryThingSpeak;
#endif
