/**
Nefry Config

Copyright (c) 2016 wami

This software is released under the MIT License.
http://opensource.org/licenses/mit-license.php
*/

/*
ModuleID	: Nefryモジュール名 & Nefryが発信するSSID
ModulePass	: Nefryが発信するWiFiパスワード
ModuleClass	: Nefryのモジュールが属するクラス
user		: Nefryでログイン機能を使うときに使用するユーザ名
userPass	: Nefryでログイン機能を使うときに使用するパスワード
StoreValue	: Nefryの環境変数を保存するときに使用する。(0-7)の範囲で保存する。末端に数字が追加される long型
StoreStr	: Nefryの環境変数を保存するときに使用する。(0-7)の範囲で保存する。末端に数字が追加される String型
*/

#include "NefryConfig.h"



void Nefry_Conf::beginWeb() {
	NefryWebServer.getWebServer()->on("/config", [&]() {
		String content = F("<h1>Nefry DataStore Setup</h1><p>このページはプログラム内から読み書きした値を表示、編集することができます。</p>"
			"<p>わざわざプログラムを書き換えずに値を変更できるためWebサービスでアクセスキーが必要になる場合など環境変数として扱うことができます。</p>"
			"<ul><li>setStoreValue or setStoreStr : 値の保存</li><li>getStoreValue or getStoreStr : 値の取得</li><li>setStoreTitle : 内容の表示</li></ul>"
			"<p>それぞれの関数の使い方はNefry公式サイトをご覧になるか、サンプルプログラムを参考にしてください。</p><form method='get'action='set_config'>");
		int formNumber, printCounter = 0;
		for (formNumber = 0; formNumber < 10; formNumber++) {
			if (htmlPrint[formNumber] == true) {
				content += F("<div class=\"row\"><label>");
				content += module_input[formNumber];
				content += F("</label><div><input name=\"smo");
				content += formNumber;
				content += F("\"maxlength=\"128\"value=\"");
				content += NefryDataStore.getStorageStr(formNumber);
				content += F("\"></div></div>");
				printCounter++;
			}
		}
		for (formNumber = 10; formNumber < 20; formNumber++) {
			if (htmlPrint[formNumber] == true) {
				content += F("<div class=\"row\"><label>");
				content += module_input[formNumber];
				content += F("</label><div><input name=\"imo");
				content += formNumber - 10;
				content += F("\"type=\"number\"value=\"");
				content += NefryDataStore.getStorageValue(formNumber - 10);
				content += F("\"></div></div>");
				printCounter++;
			}
		}
		delay(1);
		if (printCounter == 0) {
			content += F("<p>表示するものがひとつもありません。setStoreTitle関数を使って表示をするか、WriteModeにしてください。</p>");

		}
		else {
			content += F("<div class=\"row\"><div><input type=\"button\"value=\"Save\"onclick=\"return jsSubmit(this.form);\"></div></form></div>");
		}
		content += F("<div class=\"writemode\">");
		if (Nefry.getWriteMode())content += "WriteMode";
		content += F("</div><a href=\"/\">Back to top</a>");
		NefryWebServer.getWebServer()->send(200, "text/html", NefryWeb.createHtml(F("Nefry DataStore"), "", content));
	});

	NefryWebServer.getWebServer()->on("/set_config", [&]() {
		char webarg[5] = { "smo0" };
		for (int i = 0; i < 10; i++) {
			webarg[3] = '0' + i;
			String s = NefryWebServer.getWebServer()->arg(webarg);
#ifdef DEBUG_ESP_HTTP_SERVER
			DEBUG_OUTPUT.print(webarg);
			DEBUG_OUTPUT.print(" : ");
			DEBUG_OUTPUT.println(s);
#endif
			NefryDataStore.setStorageStr(s, i);
		}
		webarg[0] = 'i';
		for (int i = 0; i < 10; i++) {
			webarg[3] = '0' + i;
			String s = NefryWebServer.getWebServer()->arg(webarg);
#ifdef DEBUG_ESP_HTTP_SERVER
			DEBUG_OUTPUT.print(webarg);
			DEBUG_OUTPUT.print(" : ");
			DEBUG_OUTPUT.println(s);
#endif
			NefryDataStore.setStorageValue(s.toInt(), i);
		}
		NefryWebServer.getWebServer()->send(200, "text/html", NefryWeb.createHtml(F("Nefry DataStore Set"), "", F("<h1>Nefry Module Set</h1><p>Saveing & Restart...</p><a href=\"/\">Back to top</a>")));
		NefryWebServer.resetTimer(2);
	});
}
/* HTMLに表示するのか */
void Nefry_Conf::setStoreTitle(const char set[15], const int num) {
	if (0 <= num&&num < 20) {
		strcpy(module_input[num], set);
		htmlPrint[num] = true;
	}

}


void Nefry_Conf::begin()
{
	for (int i = 0; i < 10; i++) {
		sprintf(module_input[i], "String %d", i);
		sprintf(module_input[10 + i], "Value %d", 10 + i);
		if (Nefry.getWriteMode()) {
			htmlPrint[i] = true;
			htmlPrint[10 + i] = true;
		}
		else {
			htmlPrint[i] = false;
			htmlPrint[10 + i] = false;
		}
	}
}
Nefry_Conf NefryConfig;