/*
 * Nefryambient.h - Library for sending data to Ambient
 * Created by wami,1 9, 2016
 */
#ifndef NefryAmbient_h
#define NefryAmbient_h

#include "include/Ambient.h"
#include <Nefry.h>
#include <WiFi.h>

class NefryAmbient
{
public:

    NefryAmbient(void);
	bool begin(char channelid = 10, char keyid = 0);
    bool begin(unsigned int channelId , const char * writeKey );
    bool set(int field,const char * data);
	bool set(int field, double data);
	bool set(int field, int data);
    bool clear(int field);

    bool send(void);
    int bulk_send(char * buf);
    bool delete_data(const char * userKey);

private:
	Ambient _ambient;
	bool _conectionFlag;
};

#endif // NefryAmbient_h
