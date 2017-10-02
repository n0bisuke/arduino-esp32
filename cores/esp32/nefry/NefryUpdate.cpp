/**
Nefry lib

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "NefryUpdate.h"
void Nefry_Update::setupWebLocalUpdate(void) {
	int updateTotalSize,updateCurrentSize = 0;
	int count = 0;
	bool err = false;
	NefryWebServer.getWebServer()->on("/update", HTTP_GET, [&]() {
		Nefry.print("UPDNF");
		NefryWebServer.getWebServer()->send(200, "text/html", NefryWeb.createHtml(F("Nefry Upload Sketch"), "",
			F("<h1>Upload Sketch</h1> <p>Upload a binary file of sketch.</p><form id=\"form1\">"
				"<input type=\"file\" name=\"sketch\"><div class=\"footer\"><button type=\"button\" onclick=\"ExecUpload()\">Upload</button></div></form>"
				"Update Status : <progress id=\"prog1\" max=100 value=0 width:\"auto\"></progress><span id=\"pv\" >0</span>% <span id=\"end\" ></span><br><a href=\"/\">Back to top</a>"
				"<script type=\"text/javascript\">\n"
				"    function ExecUpload() {\n"
				"      var progressValue = document.getElementById('pv');\n"
				"      var endvalue = document.getElementById('end');\n"
				"      var o = document.getElementById('prog1');\n"
				"      var formObj = document.getElementById(\"form1\");\n"
				"      var data = new FormData(formObj);\n"
				"      var xmlhttp;\n"
				"	   if (window.XMLHttpRequest) {\n"
				"        xmlhttp = new XMLHttpRequest();\n"
				"      } else {\n"
				"        xmlhttp = new ActiveXObject(\"Microsoft.XMLHTTP\");\n"
				"      }\n"
				"      xmlhttp.open(\"POST\", \"/upload_sketch\", true);\n"
				"      xmlhttp.onreadystatechange = function () {\n"
				"        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {\n"
				"         endvalue.innerHTML =xmlhttp.responseText;\n"
				"        }\n"
				"      };\n"
				"      xmlhttp.upload.addEventListener(\"progress\", function(ev){\n"
				"         console.log(ev.loaded,ev.total);\n"
				"         o.value = ev.loaded/ ev.total*100;\n"
				"         progressValue.innerHTML =Math.floor(ev.loaded/ ev.total*100);\n"
				"      });\n"
				"      xmlhttp.send(data);\n"
				"    }\n"
				"</script>\n")));
	});

	NefryWebServer.getWebServer()->onFileUpload([&]() {
		if (NefryWebServer.getWebServer()->uri() != "/upload_sketch") return;
		Nefry.setNefryState(1);
		
		HTTPUpload& upload = NefryWebServer.getWebServer()->upload();
		updateTotalSize  = upload.totalSize;
		String file_name = String(upload.filename.c_str());
		count++;
		delay(1);
		if (file_name.endsWith("bin")) {
			err = false;
			if (upload.status == UPLOAD_FILE_START) {
				Nefry.setLedBlink(0,125, 0, true, 10);
				Serial.println("ok");
				Serial.setDebugOutput(true);
				if (!Update.begin())Update.printError(Serial);
			}
			else if (upload.status == UPLOAD_FILE_WRITE) {
				updateCurrentSize += upload.currentSize;
				if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
					Update.printError(Serial);
					Nefry.setLed(0xFF, 0x0, 0x0);
					delay(1000);
					Nefry.setLed(0xFF, 0x0, 0x0, 0);
					err = true;
					Nefry.println(F("File Err. Failed to update"));
					Nefry.setNefryState(0);
				}
			}
			else if (upload.status == UPLOAD_FILE_END) {
				if (Update.end(true)) {
					Nefry.print("Update Success:"+ (String)upload.totalSize +"\nRebooting...\n");
				}
				else {
					Update.printError(Serial);
					Nefry.setLed(0xFF, 0x0, 0x0);
					delay(1000);
					err = true;
					Nefry.println(F("File Err. Failed to update"));
					Nefry.setNefryState(0);
				}
				Serial.setDebugOutput(false);
			}
			yield();
		}
		else {
			Serial.println(F("err"));
			Nefry.println(F("File Err. Failed to update"));
			Nefry.setNefryState(0);
			err = true;
		}
	});

	NefryWebServer.getWebServer()->on("/upload_sketch", HTTP_POST, [&]() {
		Nefry.clearConsole();
		if (err == false) {
			Nefry.setLedBlink(0, 0, 255, true, 100);
			Nefry.println((Update.hasError()) ? "Update Err" : "Upload Success");
			NefryWebServer.getWebServer()->send(200, "text/html", (Update.hasError()) ? "Update Err" : "Upload Success");
		}
		else {
			Nefry.println(F("Failed to update"));
			NefryWebServer.getWebServer()->send(200, "text/html", F("Failed to update"));
			Nefry.setNefryState(0);
			Nefry.setLedBlink(0, 0, 0, false, 100);
		}
		if (err == false) {
			for (int i = 0; i < 10; i++) {
				NefryWebServer.run();
				delay(100);
			}
			Nefry.reset();
		}
		Nefry.setLedBlink(0, 0, 0, false, 100);
		Nefry.setNefryState(0);
	});
}

void Nefry_Update::beginWeb()
{
	setupWebLocalUpdate();
	//setupWebOnlineUpdate();
}

/*
int Nefry_lib::autoUpdate(String url, String domain) {
	pushSW_flg = 1;
	IPAddress ip = WiFi.localIP();
	if (ip.toString().equals("0.0.0.0")) {
		println(F("not connected to the Internet"));
	}
	else {
		println(F("autoUpdateStart"));
		ESPhttpUpdate.rebootOnUpdate(false);
		switch (ESPhttpUpdate.update(domain, 80, "/nefry.php", url)) {
		case HTTP_UPDATE_FAILED:
			pushSW_flg = 0;
			Serial.println(url);
			println(F("[update] Update failed."));
			Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
			println(ESPhttpUpdate.getLastErrorString().c_str());
			return ESPhttpUpdate.getLastError();
			break;
		case HTTP_UPDATE_NO_UPDATES:
			pushSW_flg = 0;
			println(F("[update] no Update."));
			return true;
			break;
		case HTTP_UPDATE_OK:
			println(F("[update] Update ok."));
			delay(2000);
			reset();
			break;
		}
	}
	pushSW_flg = 0;
	return false;
}

void Nefry_lib::setWebUpdate(String program_domain, String program_url) {
	pushSW_flg = 1;
	ClearConsole();
	IPAddress ip = WiFi.localIP();
	nefry_server.send(200, "text/html", createHtml(F("Nefry Web Update"),
		F("<script type=\"text/javascript\" src=\"consolejs\"></script><script type=\"text/javascript\">reload(10000);</script>"),
		F("<h1>Nefry Web Update</h1><p>自動で読み込まれるのでしばらくお待ちください。</p><div id=\"ajaxDiv\"></div><a href='/'>Back to top</a>")));
	ndelay(500);
	if (ip.toString().equals("0.0.0.0")) {
		println(F("Internet connection ... NG"));
		println(F("[UPDATE]It is not connected to the Internet.Please connect to the Internet ."));
	}
	else {
		println(F("Internet connection ... OK"));
		if (program_domain.length() > 0) {
			if (program_url.length() > 0)program_url = escapeParameter(program_url);
			//print(program_url);
			program_url.concat("/arduino.bin");
			ESPhttpUpdate.rebootOnUpdate(false);
			String UPurl;
			switch (ESPhttpUpdate.update(program_domain, 80, program_url)) {
			case HTTP_UPDATE_FAILED:
				Serial.println(program_url);
				UPurl += program_domain;
				UPurl += program_url;
				print(F("[UPDATE]アップデートに必要な情報が"));
				println(F("正しくありません。Update failed."));
				print(F("[UPDATE]URLを確認してください。"));
				print(F("Please check this URL : http://"));
				println(UPurl);
				print("ENDUP");
				break;
			case HTTP_UPDATE_NO_UPDATES:
				print(F("[UPDATE] アップデートはありません。"));
				println(F("	Update no Updates."));
				print("ENDUP");
				break;
			case HTTP_UPDATE_OK:
				print(F("[UPDATE] 更新完了、再起動します。"));
				println(F("Update OK"));
				print("ENDUP");
				ndelay(1000);
				Nefry.setLedBlink(0x00, 0xff, 0xff, 250, 10);
				Serial.println(F("[update] Update ok."));
				ndelay(4000);
				Nefry.setLed(0x00, 0xff, 0xff);
				ndelay(1000);
				reset();
				break;
			}
		}
		else {
			Serial.println(F("Rejected empty URL."));
			pushSW_flg = 0;
			println(F("[UPDATE]Empty URL is not acceptable."));
			print("ENDUP");
		}
	}

	pushSW_flg = 0;
}

void Nefry_Update::setupWebOnlineUpdate(void) {
	NefryWebServer.getWebServer()->on("/web_update", [&]() {
		NefryWebServer.getWebServer()->send(200, "text/html", NefryWeb.createHtml(F("Nefry Web Update"), F("<style>label{margin:6px;width:200px;}input{margin:6px;width:95%;}</style>"),
			F("<h1>Nefry Web Update</h1>"
				"<form method='get' action='program'><label>Program download Domain</label><input name='domain'id='URL' value='program.nefry.studio'><label>Program download URL</label><input name='URL'id='URL'  value=''>"
				"<input type=\"button\" value=\"update\" onclick=\"return jsSubmit(this.form);\"></form><br><p>Default Program Download URL : program.nefry.studio</p><a href='/'>Back to top</a>")));
	});
	NefryWebServer.getWebServer()->on("/program", [&]() {
		setUpdateWeb(NefryWebServer.getWebServer()->arg("domain"), NefryWebServer.getWebServer()->arg("URL"));
	});
}


int Nefry_Update::setUpdateWeb(String host, String url)
{
	WiFiClient _client;
	Serial.println("Connecting to: " + String(host));
	// Connect to S3
	if (_client.connect(host.c_str(), 80)) {
		// Connection Succeed.
		// Fecthing the bin
		if (url.length() >= 1 && url.indexOf("/") == 0) {
			url = "/" + url;
		}
		url.concat("/nefry32.bin");

		Serial.println("Fetching Bin: " + String(url));

		// Get the contents of the bin file
		_client.print(String("GET ") + url + " HTTP/1.1\r\n" +
			"Host: " + host + "\r\n" +
			"Cache-Control: no-cache\r\n" +
			"Connection: close\r\n\r\n");

		// Check what is being sent
		//    Serial.print(String("GET ") + bin + " HTTP/1.1\r\n" +
		//                 "Host: " + host + "\r\n" +
		//                 "Cache-Control: no-cache\r\n" +
		//                 "Connection: close\r\n\r\n");

		unsigned long timeout = millis();
		while (_client.available() == 0) {
			if (millis() - timeout > 5000) {
				Serial.println("Client Timeout !");
				_client.stop();
				return -1;
			}
		}
		// Once the response is available,
		// check stuff

		//
		//Response Structure
		//HTTP/1.1 200 OK
		//x-amz-id-2: NVKxnU1aIQMmpGKhSwpCBh8y2JPbak18QLIfE+OiUDOos+7UftZKjtCFqrwsGOZRN5Zee0jpTd0=
		//x-amz-request-id: 2D56B47560B764EC
		//Date: Wed, 14 Jun 2017 03:33:59 GMT
		//Last-Modified: Fri, 02 Jun 2017 14:50:11 GMT
		//ETag: "d2afebbaaebc38cd669ce36727152af9"
		//Accept-Ranges: bytes
		//Content-Type: application/octet-stream
		//Content-Length: 357280
		//Server: AmazonS3

		//{{BIN FILE CONTENTS}}

		while (_client.available()) {
			// read line till /n
			String line = _client.readStringUntil('\n');
			// remove space, to check if the line is end of headers
			line.trim();

			// if the the line is empty,
			// this is end of headers
			// break the while and feed the
			// remaining `_client` to the
			// Update.writeStream();
			if (!line.length()) {
				//headers ended
				break; // and get the OTA started
			}

			// Check if the HTTP Response is 200
			// else break and Exit Update
			if (line.startsWith("HTTP/1.1")) {
				if (line.indexOf("200") < 0) {
					Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
					break;
				}
			}

			// extract headers here
			// Start with content length
			if (line.startsWith("Content-Length: ")) {
				contentLength = atoi((getHeaderValue(line, "Content-Length: ")).c_str());
				Serial.println("Got " + String(contentLength) + " bytes from server");
			}

			// Next, the content type
			if (line.startsWith("Content-Type: ")) {
				String contentType = getHeaderValue(line, "Content-Type: ");
				Serial.println("Got " + contentType + " payload.");
				if (contentType == "application/octet-stream") {
					isValidContentType = true;
				}
			}
		}
	}
	else {
		// Connect to S3 failed
		// May be try?
		// Probably a choppy network?
		Serial.println("Connection to " + String(host) + " failed. Please check your setup");
		// retry??
		// execOTA();
	}

	// Check what is the contentLength and if content type is `application/octet-stream`
	Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

	// check contentLength and content type
	if (contentLength && isValidContentType) {
		// Check if there is enough to OTA Update
		bool canBegin = Update.begin(contentLength);

		// If yes, begin
		if (canBegin) {
			Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
			// No activity would appear on the Serial monitor
			// So be patient. This may take 2 - 5mins to complete
			size_t written = Update.writeStream(_client);

			if (written == contentLength) {
				Serial.println("Written : " + String(written) + " successfully");
			}
			else {
				Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?");
				// retry??
				// execOTA();
			}

			if (Update.end()) {
				Serial.println("OTA done!");
				if (Update.isFinished()) {
					Serial.println("Update successfully completed. Rebooting.");
					ESP.restart();
					return 0;//OTA成功
				}
				else {
					Serial.println("Update not finished? Something went wrong!");
					return -4;//更新中にエラーが発生しました
				}
			}
			else {
				Serial.println("Error Occurred. Error #: " + String(Update.getError()));
				return -4;//更新中にエラーが発生しました
			}
		}
		else {
			// not enough space to begin OTA
			// Understand the partitions and
			// space availability
			Serial.println("Not enough space to begin OTA");
			_client.flush();
			return -3;//OTAが実行できませんでした
		}
	}
	else {
		Serial.println("There was no content in the response");
		_client.flush();
		return -2;//データなし
	}
}
// Utility to extract header value from headers
String Nefry_Update::getHeaderValue(String header, String headerName) {
	return header.substring(strlen(headerName.c_str()));
}
*/
Nefry_Update NefryUpdate;