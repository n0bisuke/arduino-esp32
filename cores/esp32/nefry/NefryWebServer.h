#ifndef NefryWebServer_h
#define NefryWebServer_h

#include "./inc/WiFi/src/WiFi.h"
#include <Arduino.h>

#include "Nefry.h"
#include "NefryWeb.h"
#include "NefryWiFi.h"
#include "NefryConfig.h"

#define HTTP_DOWNLOAD_UNIT_SIZE 1460
#define HTTP_UPLOAD_BUFLEN 2048
#define HTTP_MAX_DATA_WAIT 1000 //ms to wait for the client to send the request
#define HTTP_MAX_POST_WAIT 1000 //ms to wait for POST data to arrive
#define HTTP_MAX_CLOSE_WAIT 2000 //ms to wait for the client to close the connection

#define CONTENT_LENGTH_UNKNOWN ((size_t) -1)
#define CONTENT_LENGTH_NOT_SET ((size_t) -2)

class Nefry_webserver
{
public:
	void
		begin(),
		run(),
		resetTimer(int delaySec);
	String arg(String name); 
private:
	WiFiServer		_server;
	WiFiClient		_currentClient;
	String			_responseHeaders;
	size_t          _contentLength;
	bool resetFlg;
	int countdown;
	void 
		sendHeader(const String& name, const String& value, bool first = false),
		_prepareHeader(String& response, int code, const char* content_type, size_t contentLength),
		send(int code, const char* content_type, const String& content),
		sendContent(const String& content);
	String escapeParameter(String param);
	String _responseCodeToString(int code);
	void _parseArguments(String data);
	struct RequestArgument {
		String key;
		String value;
	};
	int _currentArgCount;
	RequestArgument* _currentArgs;
};
extern Nefry_webserver NefryWebServer;
#endif
