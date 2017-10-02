/**
Nefry FastSensing

Copyright (c) 2017 wami

*/

#include "NefryFastSensing.h"
String _deviceID, _channelID1,_channelID2, _channelID3;
void NefryFastSensing::begin(String deviceID,const char channel1[9],const char channel2[9],const char channel3[9]){
	_deviceID = deviceID;
	channelKey[0] = channel1;
	channelKey[1] = channel2;
	channelKey[2] = channel3;
	for (int i = 0; i < 3; i++) {
		dataFlg[i] = false;
	}
	sendData = "";
}

void NefryFastSensing::begin(int deviceID, int channel1, int channel2, int channel3)
{
	begin(Nefry.getStoreStr(deviceID), Nefry.getStoreStr(channel1).c_str(), Nefry.getStoreStr(channel2).c_str(), Nefry.getStoreStr(channel3).c_str());
}

bool NefryFastSensing::push() {
	for (int i = 0; i < 3; i++) {
		dataFlg[i] = false;
	}
	HTTPClient http;
	http.begin("http://f-io.net/d1/"+ _deviceID +"?"+sendData); //HTTP
	sendData = "";
	//http.addHeader("Content-Type", "application/json");
	int httpCode = http.GET();
	// httpCode will be negative on error
	if (httpCode > 0) {
		// HTTP header has been send and Server response header has been handled
		Serial.printf("[HTTP] GET... code: %d\n", httpCode);

		// file found at server
		if (httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			Serial.println(payload);
			return true;
		}
		else {
			String payload = http.getString();
			Serial.println(payload);
			http.end();
			return false;
		}
	}
	else {
		Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
		http.end();
		return false;
	}

	http.end();
	return true;
}

bool NefryFastSensing::setValue(unsigned char channelNum, String v)
{
	if (channelNum > 2)return false;
	if (dataFlg[channelNum] == false) {
		sendData += channelKey[channelNum];
		sendData += "=" + v + "&";
	}
	else {
		return false;
	}
	dataFlg[channelNum] = true;
	return true;
}

bool NefryFastSensing::setValue(unsigned char channelNum, double v)
{
	return setValue(channelNum, (String) v);
}

bool NefryFastSensing::setValue(unsigned char channelNum, int v)
{
	return setValue(channelNum,(String) v);
}

/*
DataElement::DataElement() {
	params = aJson.createArray();
	paJsonObj = aJson.createObject();
	aJson.addStringToObject(paJsonObj, "api_version", "2016-05-02");
	aJson.addStringToObject(paJsonObj, "resource_type", "channel_data");
	aJson.addStringToObject(paJsonObj, "action", "update");
	aJson.addStringToObject(paJsonObj, "device_token", _deviceID.c_str());
	aJson.addItemToObject(paJsonObj, "resource", params);
}
DataElement::DataElement(char *json_string) {
	params = aJson.parse(json_string);
}

DataElement::~DataElement() {
	aJson.deleteItem(paJsonObj);
	paJsonObj = NULL;
	params = NULL;
}

void DataElement::setValue(unsigned char channelNum, const char *v) {
	aJsonObject *dataparams = aJson.createObject();
	switch (channelNum)
	{
	case 0:
		aJson.addStringToObject(dataparams, "token", _channelID1.c_str());
		break;
	case 1:
		aJson.addStringToObject(dataparams, "token", _channelID2.c_str());
		break;
	case 2:
		aJson.addStringToObject(dataparams, "token", _channelID3.c_str());
		break;
	default:
		break;
	}
	aJson.addStringToObject(dataparams, "value", v);
	aJson.addItemToArray(params, dataparams);
}

void DataElement::setValue(unsigned char channelNum, int v) {
	aJsonObject *dataparams = aJson.createObject();
	switch (channelNum)
	{
	case 0:
		aJson.addStringToObject(dataparams, "token", _channelID1.c_str());
		break;
	case 1:
		aJson.addStringToObject(dataparams, "token", _channelID2.c_str());
		break;
	case 2:
		aJson.addStringToObject(dataparams, "token", _channelID3.c_str());
		break;
	default:
		break;
	}
	aJson.addNumberToObject(dataparams, "value", v);
	aJson.addItemToArray(params, dataparams);
}

void DataElement::setValue(unsigned char channelNum, double v) {
	aJsonObject *dataparams = aJson.createObject();
	switch (channelNum)
	{
	case 0:
		aJson.addStringToObject(dataparams, "token", _channelID1.c_str());
		break;
	case 1:
		aJson.addStringToObject(dataparams, "token", _channelID2.c_str());
		break;
	case 2:
		aJson.addStringToObject(dataparams, "token", _channelID3.c_str());
		break;
	default:
		break;
	}
	aJson.addNumberToObject(dataparams, "value", v);
	aJson.addItemToArray(params, dataparams);
}

char *DataElement::getString(const char *key) {
	aJsonObject* obj = aJson.getObjectItem(params, key);
	if (obj == NULL) {
		Serial.println("obj is NULL");
		return (char*)"";
	}
	return obj->valuestring;
}

int DataElement::getInt(const char *key) {
	aJsonObject* obj = aJson.getObjectItem(params, key);
	if (obj == NULL) {
		Serial.println("obj is NULL");
		return 0;
	}
	return obj->valueint;
}

float DataElement::getFloat(const char *key) {
	aJsonObject* obj = aJson.getObjectItem(params, key);
	if (obj == NULL) {
		Serial.println("obj is NULL");
		return 0;
	}
	return obj->valuefloat;
}


char *DataElement::toCharArray() {
	return aJson.print(paJsonObj);
}

unsigned char DataElement::getArraySize() {
	String s = aJson.print(paJsonObj);
	return s.length();
}
*/