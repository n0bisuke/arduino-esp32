#ifndef NefryFastSensing_h
#define NefryFastSensing_h

#include <HTTPClient.h>
#include <Nefry.h>
/*
#include "include/aJson/aJson.h"
class DataElement {
public:
	DataElement();
	DataElement(char *json_string);
	~DataElement();
	void setValue(unsigned char channelNum, const char *v);
	void setValue(unsigned char channelNum, int v);
	void setValue(unsigned char channelNum, double v);
	char *toCharArray();
	char *getString(const char *key);
	int getInt(const char *key);
	float getFloat(const char *key);
	unsigned char getArraySize();
private:
	aJsonObject *params;
	aJsonObject *paJsonObj;
};
*/
class NefryFastSensing
{
public:
	bool push(),
		 setValue(unsigned char channelNum, int v),
		 setValue(unsigned char channelNum, String v),
		 setValue(unsigned char channelNum, double v);
	void begin(String deviceID, char channel1[9], char channel2[9], char channel3[9]);
private:
	bool dataFlg[3];
	char* channelKey[3];
	String sendData;
};
#endif
