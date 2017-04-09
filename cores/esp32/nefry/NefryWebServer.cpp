/**
Nefry lib

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/
#include "NefryWebServer.h"
//WiFiServer _server(80);
void Nefry_webserver::begin() {
	_server = WiFiServer(80);
	_server.begin();
	resetFlg = false;
}

void Nefry_webserver::resetTimer(int delaySec)
{
	resetFlg = true;
	countdown = delaySec*10;
}

void Nefry_webserver::run() {
	bool deleteFlg;
	if (resetFlg == true) {
		countdown -= 1;
		Serial.println(countdown);
		if (countdown <= 0) {
			Nefry.reset();
		}
	}
	WiFiClient client = _server.available();   // listen for incoming clients

	if (!client) {
		return;
	}
	String req = client.readStringUntil('\r');
	client.readStringUntil('\n');
	int addr_start = req.indexOf(' ');
	int addr_end = req.indexOf(' ', addr_start + 1);
	if (addr_start == -1 || addr_end == -1) {
		return;
	}
	_currentClient = client;
	String url = req.substring(addr_start + 1, addr_end);
	String searchStr = "";
	int hasSearch = url.indexOf('?');
	if (hasSearch != -1) {
		searchStr = url.substring(hasSearch + 1);
		url = url.substring(0, hasSearch);
		_parseArguments(searchStr);
	}
	if (!_currentClient.connected()) {
		_currentClient = WiFiClient();
		return;
	}
	Serial.print("new client url:"); Serial.println(url);
	if (url.equalsIgnoreCase("/nefry_css")) {
		send(200, "text/css", NefryWeb.beginWeb("nefry_css"));
	}
	else if (url.equalsIgnoreCase("/reset")) {
		send(200, "text/html", NefryWeb.beginWeb("Reset"));
		_currentClient.flush();
		_currentClient = WiFiClient();
		resetTimer(2);
	}
	else if (url.equalsIgnoreCase("/onreset")) {
		send(200, "text/html", NefryWeb.beginWeb("onreset"));
		_currentClient.flush();
		_currentClient = WiFiClient();
		resetTimer(2);
	}
	else if (url.equalsIgnoreCase("/jsform")) {
		send(200, "text/html", NefryWeb.beginWeb("jsform"));
	}
	else if (url.equalsIgnoreCase("/wifi_conf")) {
		send(200, "text/html", NefryWiFi.beginWeb("wifi_conf"));
	}
	else if (url.equalsIgnoreCase("/wifiReload")) {
		send(200, "text/html", NefryWiFi.beginWeb("wifiReload"));
	}
	else if (url.equalsIgnoreCase("/wifiCount")) {
		send(200, "text/html", NefryWiFi.beginWeb("wifiCount"));
	}
	else if (url.equalsIgnoreCase("/set_wifi")) {
		String newssid = arg("ssid");
		String newpwd = arg("pwd");
		Serial.print("newssid : ");
		Serial.println(newssid);
		String content;
		if (newssid.length() > 0) {
			NefryWiFi.addWifi(newssid, newpwd);
			content = F("Save SSID:");
			content += newssid;
			content += F(" Restart to boot into new WiFi");
		}
		else {
			content = F("Empty SSID is not acceptable.");
		}
		send(200, "text/html", NefryWeb.createHtml(F("Nefry Wifi Set"), "", (String)F("<h1>Nefry Wifi Set</h1><p>") + content + (String)F("</p><a href=\"/\">Back to top</a>")));
		Serial.print("dateSend");
		if (newssid.length() != 0)resetTimer(2);
	}
	else if (url.equalsIgnoreCase("/delete_wifi")) {
		String del = "";
		deleteFlg = false;
		for (int i = 0; i < 5; i++) {
			String data = arg("" + i);
			if (data.equals("1")) {
				del += "<li>";
				del += NefryDataStore.getConnectSSID(i);
				del += "</li>";
				NefryWiFi.deleteWifi(i);
				deleteFlg = true;
			}
		}
		NefryWiFi.saveWifi();
		send(200, "text/html", NefryWeb.createHtml(F("Nefry Wifi Delete"), "", (String)F("<h1>Nefry Wifi Delete</h1><p>Delete List</p><ul>") + del + (String)F("</ul><a href=\"/\">Back to top</a>")));
		if (deleteFlg ==true)resetTimer(2);
	}
	/* "/"は必ず一番下にすること */
	else if (url.equalsIgnoreCase("/")) {
		send(200, "text/html", NefryWeb.beginWeb("index"));
	}
	else {
		send(404, "text/html", NefryWeb.beginWeb("NotFound"));
	}
	_currentClient.flush();
	_currentClient = WiFiClient();
}

void Nefry_webserver::sendHeader(const String& name, const String& value, bool first) {
	String headerLine = name;
	headerLine += ": ";
	headerLine += value;
	headerLine += "\r\n";

	if (first) {
		_responseHeaders = headerLine + _responseHeaders;
	}
	else {
		_responseHeaders += headerLine;
	}
}
void Nefry_webserver::_prepareHeader(String& response, int code, const char* content_type, size_t contentLength) {
	response = "HTTP/1.1 ";
	response += String(code);
	response += " ";
	response += _responseCodeToString(code);
	response += "\r\n";

	if (!content_type)
		content_type = "text/html";

	sendHeader("Content-Type", content_type, true);
	sendHeader("Content-Length", String(contentLength));
	sendHeader("Connection", "close");
	sendHeader("Access-Control-Allow-Origin", "*");

	response += _responseHeaders;
	response += "\r\n";
	_responseHeaders = String();
}
void Nefry_webserver::send(int code, const char* content_type, const String& content) {
	String header;
	_prepareHeader(header, code, content_type, content.length());
	sendContent(header);
	sendContent(content);
}
void Nefry_webserver::sendContent(const String& content) {
	const size_t unit_size = HTTP_DOWNLOAD_UNIT_SIZE;
	size_t size_to_send = content.length();
	const char* send_start = content.c_str();

	while (size_to_send) {
		size_t will_send = (size_to_send < unit_size) ? size_to_send : unit_size;
		size_t sent = _currentClient.write(send_start, will_send);
		if (sent == 0) {
			break;
		}
		size_to_send -= sent;
		send_start += sent;
	}
}
String Nefry_webserver::_responseCodeToString(int code) {
	switch (code) {
	case 100: return F("Continue");
	case 101: return F("Switching Protocols");
	case 200: return F("OK");
	case 201: return F("Created");
	case 202: return F("Accepted");
	case 203: return F("Non-Authoritative Information");
	case 204: return F("No Content");
	case 205: return F("Reset Content");
	case 206: return F("Partial Content");
	case 300: return F("Multiple Choices");
	case 301: return F("Moved Permanently");
	case 302: return F("Found");
	case 303: return F("See Other");
	case 304: return F("Not Modified");
	case 305: return F("Use Proxy");
	case 307: return F("Temporary Redirect");
	case 400: return F("Bad Request");
	case 401: return F("Unauthorized");
	case 402: return F("Payment Required");
	case 403: return F("Forbidden");
	case 404: return F("Not Found");
	case 405: return F("Method Not Allowed");
	case 406: return F("Not Acceptable");
	case 407: return F("Proxy Authentication Required");
	case 408: return F("Request Time-out");
	case 409: return F("Conflict");
	case 410: return F("Gone");
	case 411: return F("Length Required");
	case 412: return F("Precondition Failed");
	case 413: return F("Request Entity Too Large");
	case 414: return F("Request-URI Too Large");
	case 415: return F("Unsupported Media Type");
	case 416: return F("Requested range not satisfiable");
	case 417: return F("Expectation Failed");
	case 500: return F("Internal Server Error");
	case 501: return F("Not Implemented");
	case 502: return F("Bad Gateway");
	case 503: return F("Service Unavailable");
	case 504: return F("Gateway Time-out");
	case 505: return F("HTTP Version not supported");
	default:  return "";
	}
}
#define DEBUG_OUTPUT Serial
#define DEBUG_ESP_HTTP_SERVER
void Nefry_webserver::_parseArguments(String data) {
	if (_currentArgs)
		delete[] _currentArgs;
	_currentArgCount = 0;
#ifdef DEBUG_ESP_HTTP_SERVER
	DEBUG_OUTPUT.print("args: ");
	DEBUG_OUTPUT.println(data);
#endif
	if (data.length() == 0)return;
	_currentArgCount = 1;
	for (int i = 0; i < (int)data.length(); ) {
		i = data.indexOf('&', i);
		if (i == -1)
			break;
		++i;
		++_currentArgCount;
	}
#ifdef DEBUG_ESP_HTTP_SERVER
	DEBUG_OUTPUT.print("args count: ");
	DEBUG_OUTPUT.println(_currentArgCount);
#endif

	_currentArgs = new RequestArgument[_currentArgCount];
	int pos = 0;
	int iarg;
	for (iarg = 0; iarg < _currentArgCount;) {
		int equal_sign_index = data.indexOf('=', pos);
		int next_arg_index = data.indexOf('&', pos);
#ifdef DEBUG_ESP_HTTP_SERVER
		DEBUG_OUTPUT.print("pos ");
		DEBUG_OUTPUT.print(pos);
		DEBUG_OUTPUT.print("=@ ");
		DEBUG_OUTPUT.print(equal_sign_index);
		DEBUG_OUTPUT.print(" &@ ");
		DEBUG_OUTPUT.println(next_arg_index);
#endif
		if ((equal_sign_index == -1) || ((equal_sign_index > next_arg_index) && (next_arg_index != -1))) {
#ifdef DEBUG_ESP_HTTP_SERVER
			DEBUG_OUTPUT.print("arg missing value: ");
			DEBUG_OUTPUT.println(iarg);
#endif
			if (next_arg_index == -1)
				break;
			pos = next_arg_index + 1;
			continue;
		}
		RequestArgument& arg = _currentArgs[iarg];
		arg.key = data.substring(pos, equal_sign_index);
		arg.value = escapeParameter(data.substring(equal_sign_index + 1, next_arg_index));
#ifdef DEBUG_ESP_HTTP_SERVER
		DEBUG_OUTPUT.print("arg ");
		DEBUG_OUTPUT.print(iarg);
		DEBUG_OUTPUT.print(" key: ");
		DEBUG_OUTPUT.print(arg.key);
		DEBUG_OUTPUT.print(" value: ");
		DEBUG_OUTPUT.println(arg.value);
#endif
		++iarg;
		if (next_arg_index == -1)
			break;
		pos = next_arg_index + 1;
	}
	_currentArgCount = iarg;
#ifdef DEBUG_ESP_HTTP_SERVER
	DEBUG_OUTPUT.print("args count: ");
	DEBUG_OUTPUT.println(_currentArgCount);
#endif

}
String Nefry_webserver::arg(String name) {
	for (int i = 0; i < _currentArgCount; ++i) {
		if (_currentArgs[i].key.equals(name))
			return _currentArgs[i].value;
	}
	return String();
}
String Nefry_webserver::escapeParameter(String param) {
	param.replace("+", " ");
	param.replace("%21", "!");
	param.replace("%22", "\"");
	param.replace("%23", "#");
	param.replace("%24", "$");
	param.replace("%25", "%");
	param.replace("%26", "&");
	param.replace("%27", "'");
	param.replace("%28", "(");
	param.replace("%29", ")");
	param.replace("%2A", "*");
	param.replace("%2B", "+");
	param.replace("%2C", ",");
	param.replace("%2F", "/");
	param.replace("%3A", ":");
	param.replace("%3B", ";");
	param.replace("%3C", "<");
	param.replace("%3D", "=");
	param.replace("%3E", ">");
	param.replace("%3F", "?");
	param.replace("%40", "@");
	param.replace("%5B", "[");
	param.replace("%5C", "\\");
	param.replace("%5D", "]");
	param.replace("%5E", "^");
	param.replace("%60", "'");
	param.replace("%7B", "{");
	param.replace("%7C", "|");
	param.replace("%7D", "}");
	return param;
}


Nefry_webserver NefryWebServer;