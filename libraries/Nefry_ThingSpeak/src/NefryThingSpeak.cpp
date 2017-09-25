/**
Nefry FastSensing

Copyright (c) 2017 wami

*/

#include "NefryThingSpeak.h"

NefryThingSpeakClass NefryThingSpeak;

void NefryThingSpeakClass::begin(int nefryConfigChannelNumber, const char* hint)
{
	ThingSpeak.begin(_nefryThingClient);
	_nefryConfigChannelNumber = nefryConfigChannelNumber;
	Nefry.setStoreTitleValue(hint, _nefryConfigChannelNumber);
}

void NefryThingSpeakClass::setWriteAPIKey(int nefryConfigWriteApikey, const char* hint)
{
	_nefryConfigWriteApikey = nefryConfigWriteApikey;
	Nefry.setStoreTitleStr(hint, _nefryConfigWriteApikey);
}

void NefryThingSpeakClass::setReadAPIKey(int nefryConfigReadApikey, const char* hint)
{
	_nefryConfigReadApikey = nefryConfigReadApikey;
	Nefry.setStoreTitleStr(hint, _nefryConfigReadApikey);
}

const char * NefryThingSpeakClass::getWriteAPIKey()
{
	_nefryWriteAPIKey = Nefry.getStoreStr(_nefryConfigWriteApikey);
	return _nefryWriteAPIKey.c_str();
}

const char * NefryThingSpeakClass::getReadAPIKey()
{
	_nefryReadAPIKey = Nefry.getStoreStr(_nefryConfigReadApikey);
	return _nefryReadAPIKey.c_str();
}

unsigned long NefryThingSpeakClass::getChannelNumber()
{
	return Nefry.getStoreValue(_nefryConfigChannelNumber);
}

int NefryThingSpeakClass::writeField( unsigned int field, int value)
{
	return ThingSpeak.writeField(getChannelNumber(),field,value, getWriteAPIKey());
}

int NefryThingSpeakClass::writeField(unsigned int field, long value)
{
	return ThingSpeak.writeField(getChannelNumber(), field, value, getWriteAPIKey());
}

int NefryThingSpeakClass::writeField(unsigned int field, float value)
{
	return ThingSpeak.writeField(getChannelNumber(), field, value, getWriteAPIKey());
}

int NefryThingSpeakClass::writeField(unsigned int field, const char * value)
{
	return ThingSpeak.writeField(getChannelNumber(), field, value, getWriteAPIKey());
}

int NefryThingSpeakClass::writeField(unsigned int field, String value)
{
	return ThingSpeak.writeField(getChannelNumber(), field, value, getWriteAPIKey());
}

int NefryThingSpeakClass::writeFields()
{
	return ThingSpeak.writeFields(getChannelNumber(), getWriteAPIKey());
}

