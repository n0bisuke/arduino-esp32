/*
 * NefryAmbient.cpp - Library for sending data to Ambient
 * Created by Takehiko Shimojima, April 21, 2016
 */
#include "NefryAmbient.h"
WiFiClient _client;
NefryAmbient::NefryAmbient() {
	_ambient =Ambient();
}
bool NefryAmbient::begin(char channelid, char keyid)
{
	Nefry.setStoreTitle("ChannelID", channelid);
	Nefry.setStoreTitle("WriteKey", keyid);
	_conectionFlag = true;
	if (Nefry.getStoreValue(channelid-10) == 0 || Nefry.getStoreStr(keyid).length() == 0) {
		Nefry.println(F("Ambient Connection INFO Lack"));
		Nefry.println(F("(接続に必要な情報が不足しています)"));
		_conectionFlag = false;
		return false;
	}
	else return _ambient.begin(Nefry.getStoreValue(channelid-10), Nefry.getStoreStr(keyid).c_str(), &_client);
}

bool NefryAmbient::begin(unsigned int channelId, const char * writeKey) {
	_conectionFlag = true;
	return _ambient.begin(channelId,writeKey, &_client);
}

bool NefryAmbient::set(int field,const char * data) {
	if (_conectionFlag==false)return false;
	else return _ambient.set(field, data);
}

bool NefryAmbient::set(int field, double data){
	if (_conectionFlag==false)return false;
	else return _ambient.set(field, data);
}

bool NefryAmbient::set(int field, int data){
	if (_conectionFlag==false)return false;
	else return _ambient.set(field, data);
}

bool NefryAmbient::clear(int field) {
	if (_conectionFlag==false)return false;
	else return _ambient.clear(field);
}

bool NefryAmbient::send() {
	Nefry.ndelay(10);
	if (_conectionFlag == false)return false;
	else return _ambient.send();
}

int NefryAmbient::bulk_send(char *buf) {
	if (_conectionFlag==false)return false;
	else return _ambient.bulk_send(buf);
}

bool NefryAmbient::delete_data(const char * userKey) {
	if (_conectionFlag==false)return false;
	else return _ambient.delete_data(userKey);
}
