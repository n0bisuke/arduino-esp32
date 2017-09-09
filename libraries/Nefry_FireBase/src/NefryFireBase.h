#ifndef NefryFireBase_h
#define NefryFireBase_h

#include <WiFiClientSecure.h>
#include <Nefry.h>
#include "include/aJson/aJson.h"
class DataElement {
public:
	DataElement();
	DataElement(char *json_string);
	~DataElement();
	void setValue(const char *key, const char *v);
	void setValue(const char *key, int v);
	void setValue(const char *key, double v);
	char *toCharArray();
	char *getString(const char *key);
	int getInt(const char *key);
	float getFloat(const char *key);
	unsigned char getArraySize();
private:
	aJsonObject *params;
	aJsonObject *paJsonObj;
};

class NefryFireBase
{
public:
	bool remove(String path),
		send(String path, DataElement *element),
		update(String path, DataElement *element),
		write(String path, DataElement *element);
	void begin(String host, String auth = "");
	String read(String path);

private:
		String _host, _auth;
		String makeFirebaseURL(String path, String auth);
		bool sendPacketCreator(String path, DataElement *element, String mode);
};
#endif
