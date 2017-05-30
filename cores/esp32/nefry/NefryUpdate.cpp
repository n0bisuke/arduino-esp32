/**
Nefry lib

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

#include "NefryUpdate.h"
void Nefry_Update::setupWebLocalUpdate(void) {
	int count = 0;
	bool err = false;
	NefryWebServer.getWebServer()->on("/update", HTTP_GET, [&]() {
		Nefry.print("UPDNF");
		NefryWebServer.getWebServer()->send(200, "text/html", NefryWeb.createHtml(F("Nefry Upload Sketch"), "",
			F("<h1>Upload Sketch</h1> <p>Upload a binary file of sketch.</p><form method=\"POST\" action=\"/upload_sketch\" enctype=\"multipart/form-data\">"
				"<input type=\"file\" name=\"sketch\"><div class=\"footer\"><input type=\"submit\"value=\"Upload\"></div></form><a href=\"/\">Back to top</a>")));
	});

	NefryWebServer.getWebServer()->onFileUpload([&]() {
		if (NefryWebServer.getWebServer()->uri() != "/upload_sketch") return;
		HTTPUpload& upload = NefryWebServer.getWebServer()->upload();
		Serial.printf("Sketch: %s Uploading\n", upload.filename.c_str());
		String file_name = String(upload.filename.c_str());
		count++;
		if (file_name.endsWith("bin")) {
			err = false;
			if (count % 10 == 1) {
				Nefry.setLed(0xff, 0xff, 0x0);
				delay(10);
				Nefry.setLed(0xff, 0xff, 0x0, 0);
			}
			if (upload.status == UPLOAD_FILE_START) {
				Serial.println("ok");
				Serial.setDebugOutput(true);
				if (!Update.begin())Update.printError(Serial);
			}
			else if (upload.status == UPLOAD_FILE_WRITE) {
				if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
					Update.printError(Serial);
					Nefry.setLed(0xFF, 0x0, 0x0);
					delay(1000);
					Nefry.setLed(0xFF, 0x0, 0x0, 0);
					err = true;
					Nefry.println(F("File Err. Failed to update"));
				}
			}
			else if (upload.status == UPLOAD_FILE_END) {
				if (Update.end(true)) {
					Nefry.print("Update Success:"+ (String)upload.totalSize +"\nRebooting...\n");
					Nefry.setLed(0x0, 0x0, 0xFF);
					delay(1500);
					Nefry.setLed(0xFF, 0x0, 0x0, 0);

				}
				else {
					Update.printError(Serial);
					Nefry.setLed(0xFF, 0x0, 0x0);
					delay(1000);
					Nefry.setLed(0xFF, 0x0, 0x0, 0);
					err = true;
					Nefry.println(F("File Err. Failed to update"));
				}
				Serial.setDebugOutput(false);
			}
			yield();
		}
		else {
			if (count % 15 == 1) {
				Nefry.setLed(0xFF, 0x0, 0x0);
				delay(10);
				Nefry.setLed(0xFF, 0x0, 0x0, 0);
			}
			Serial.println(F("err"));
			Nefry.println(F("File Err. Failed to update"));
			err = true;
		}
	});

	NefryWebServer.getWebServer()->on("/upload_sketch", HTTP_POST, [&]() {
		Nefry.clearConsole();
		if (err == false) {
			Nefry.println((Update.hasError()) ? "Update Err" : "Upload Success");
		}
		else {
			Nefry.println(F("Failed to update"));
		}
		NefryWebServer.getWebServer()->send(200, "text/html", NefryWeb.createHtml(F("Nefry Upload Sketch"),
			F("<script type=\"text/javascript\" src=\"consolejs\"></script><script type=\"text/javascript\">clearInterval(timer);loadDoc();</script>"),
			F("<h1>Nefry Update</h1><div id=\"ajaxDiv\"></div><a href='/'>Back to top</a>")));
		if (err == false) {
			for (int i = 0; i < 10; i++) {
				NefryWebServer.run();
				delay(100);
			}
			Nefry.reset();
		}
	});
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

void Nefry_lib::setupWebOnlineUpdate(void) {
	nefry_server.on("/web_update", [&]() {
		nefry_server.send(200, "text/html", createHtml(F("Nefry Web Update"), F("<style>label{margin:6px;width:200px;}input{margin:6px;width:95%;}</style>"),
			F("<h1>Nefry Web Update</h1>"
				"<form method='get' action='program'><label>Program download Domain</label><input name='domain'id='URL' value='program.nefry.studio'><label>Program download URL</label><input name='URL'id='URL'  value=''>"
				"<input type=\"button\" value=\"update\" onclick=\"return jsSubmit(this.form);\"></form><br><p>Default Program Download URL : program.nefry.studio</p><a href='/'>Back to top</a>")));
	});
	nefry_server.on("/program", [&]() {
		setWebUpdate(nefry_server.arg("domain"), nefry_server.arg("URL"));
	});
}
*/
Nefry_Update NefryUpdate;