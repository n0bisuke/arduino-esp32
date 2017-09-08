/**
Nefry IFTTT lib

Copyright (c) 2015 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "NefryFireBase.h"

void NefryFireBase::begin(String host,String auth) {
	_host = host;
	_auth = auth;
}

String NefryFireBase::makeFirebaseURL(const String path, const String auth) {
	String url;
	if (path[0] != '/') {
		url = "/";
	}
	url += path + ".json";
	if (auth.length() > 0) {
		url += "?auth=" + auth;
	}
	return url;
}
bool NefryFireBase::write(String path, DataElement *element) {
	return sendPacketCreator(path, element, "PUT ");
}
bool NefryFireBase::send(String path, DataElement *element) {
	return sendPacketCreator(path, element, "POST ");
}

bool NefryFireBase::update(String path, DataElement *element) {
	return sendPacketCreator(path, element, "PATCH ");
}

bool NefryFireBase::remove(String path) {
	DataElement elem = DataElement();
	return sendPacketCreator(path, &elem, "DELETE ");
}
String NefryFireBase::read(String path) {
	WiFiClientSecure client;
	Serial.println("\nStarting connection to server...");
	if (!client.connect(_host.c_str(), 443)) {
		Serial.println("Connection failed!");
		return "Connection failed";
	}
	else {
		Serial.println("Connected to server!");
		client.print((String)"GET " + makeFirebaseURL(path, _auth) + " HTTP/1.1\r\n" +
			"Content-Type: application/json\r\n" +
			"Host: " + _host + "\r\n" +
			"Content-Length: 0\r\n" +
			"Connection: close\r\n\r\n");
		client.println();
		unsigned long timeout = millis();
		while (client.available() == 0) {
			if (millis() - timeout > 5000) {
				Serial.println(">>> Client Timeout !");
				client.stop();
				return "Timeout";
			}
		}
		// Read all the lines of the reply from server and print them to Serial
		String line;
		while (client.available()) {
			line = client.readStringUntil('\r');
			Serial.print(line);
		}
		Serial.println();
		Serial.println("closing connection");
		return line;

	}
	return "";
}

bool NefryFireBase::sendPacketCreator(String path, DataElement *element, String mode){
	WiFiClientSecure client;
	//char *send_array;
	Serial.println("\nStarting connection to server...");
	if (!client.connect(_host.c_str(), 443)) {
		Serial.println("Connection failed!");
		return false;
	}
	else {
		Serial.println("Connected to server!");
		client.print(mode + makeFirebaseURL(path,_auth) +" HTTP/1.1\r\n" +
			"Content-Type: application/json\r\n" +
			"Host: " + _host + "\r\n" +
			"Content-Length: " + element->getArraySize() + "\r\n" +
			"Connection: close\r\n\r\n");
		client.print(element->toCharArray());
		client.println();
		unsigned long timeout = millis();
		while (client.available() == 0) {
			if (millis() - timeout > 5000) {
				Serial.println(">>> Client Timeout !");
				client.stop();
				return false;
			}
		}
		// Read all the lines of the reply from server and print them to Serial
		while (client.available()) {
			String line = client.readStringUntil('\r');
			Serial.print(line);
		}
		Serial.println();
		Serial.println("closing connection");

	}
	return true;
}
DataElement::DataElement() {
	params = aJson.createObject();
}
DataElement::DataElement(char *json_string) {
	params = aJson.parse(json_string);
}

DataElement::~DataElement() {
	aJson.deleteItem(params);
	params = NULL;
}

void DataElement::setValue(const char *key, const char *v) {
	aJson.addStringToObject(params, key, v);
}

void DataElement::setValue(const char *key, int v) {
	aJson.addNumberToObject(params, key, v);
}

void DataElement::setValue(const char *key, double v) {
	aJson.addNumberToObject(params, key, v);
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
	return aJson.print(params);
}

unsigned char DataElement::getArraySize() {
	String s = aJson.print(params);
	return s.length();
}
