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
StorageValue: Nefryの環境変数を保存するときに使用する。(0-7)の範囲で保存する。末端に数字が追加される long型
StorageStr	: Nefryの環境変数を保存するときに使用する。(0-7)の範囲で保存する。末端に数字が追加される String型
*/

#include "NefryConfig.h"



String Nefry_Conf::beginWeb(String link) {

	if (link.equals("config")) {
		String content = F("<h1>Nefry DataStore Setup</h1><form method='get'action='set_config'>");
		int formNumber;
		for (formNumber = 0; formNumber < 10; formNumber++) {
			if (htmlPrint[formNumber] == 1) {
				content += F("<div class=\"row\"><label>");
				content += module_input[formNumber];
				content += F("</label><div><input name=\"smo");
				content += formNumber;
				content += F("\"maxlength=\"128\"value=\"");
				content += NefryDataStore.getStorageStr(formNumber);
				content += F("\"></div></div>");
			}
		}
		for (formNumber = 10; formNumber < 20; formNumber++) {
			if (htmlPrint[formNumber] == 1) {
				content += F("<div class=\"row\"><label>");
				content += module_input[formNumber];
				content += F("</label><div><input name=\"imo");
				content += formNumber - 10;
				content += F("\"type=\"number\"value=\"");
				content += NefryDataStore.getStorageValue(formNumber - 10);
				content += F("\"></div></div>");
			}
		}
		delay(1);
		content += F("<div class=\"psrow\"><div><input type=\"button\"value=\"Save\"onclick=\"return jsSubmit(this.form);\"></div></form></div><div class=\"writemode\">");
		if (Nefry.getWriteMode())content += "WriteMode";
		content += F("</div><a href=\"/\">Back to top</a>");
		NefryWeb.createHtml(F("Nefry DataStore"), "", content);
	}
}
				   /* HTMLに表示するのか */
void Nefry_Conf::setStoreTitle(const char set[15], const int num) {
	if (0 <= num&&num < 20) {
		strcpy(module_input[num], set);
		htmlPrint[num] = 1;
	}

}

void Nefry_Conf::begin()
{
	for (int i = 0; i < 10; i++) {
		sprintf(module_input[i], "String %d", i);
		sprintf(module_input[10+i], "Value %d", 10+i);
		if (Nefry.getWriteMode()) {
			htmlPrint[i] = 1;
			htmlPrint[10+i] = 1;
		}
		else {
			htmlPrint[i] = 0;
			htmlPrint[10 + i] = 0;
		}		
	}
}
Nefry_Conf NefryConfig;