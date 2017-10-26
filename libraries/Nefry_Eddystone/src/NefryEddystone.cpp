// Nefry Eddystone
// Copyright(C) 2017 wami
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.If not, see <http://www.gnu.org/licenses/>.

#include "sdkconfig.h"

#if defined(CONFIG_BT_ENABLED) && defined(CONFIG_BLUEDROID_ENABLED)

#include "NefryEddystone.h"
#include "esp32-hal-log.h"

#include "bt.h"
#include "bta_api.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "Arduino.h"

static esp_ble_adv_params_t _adv_params = {
	.adv_int_min = 0x20,
	.adv_int_max = 0x40,
	.adv_type = ADV_TYPE_NONCONN_IND,
	.own_addr_type = BLE_ADDR_TYPE_PUBLIC,
	.peer_addr = { 0x00, },
	.peer_addr_type = BLE_ADDR_TYPE_PUBLIC,
	.channel_map = ADV_CHNL_ALL,
	.adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

uint8_t eddystone_packet[31] = {
	0x02, 0x01, 0x06, 0x03, 0x03, 0xAA, 0xFE, 
	0x00, //Length
	0x16, 0xAA, 0xFE, 0x10, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
/*
* BLE Arduino
*
* */
bool NefryEddystone::begin(String url) {
	setUrl(url);
	for (int i = 0; i < 31; i++) {
		Serial.print(eddystone_packet[i]);
		Serial.print(":");
	}
	//Serial.println("btStart");
	if (!btStarted() && !btStart()) {
		//Serial.println("btStart failed");
		return false;
	}
	//Serial.println("esp_bluedroid_init");
	esp_bluedroid_status_t bt_state = esp_bluedroid_get_status();
	if (bt_state == ESP_BLUEDROID_STATUS_UNINITIALIZED) {
		if (esp_bluedroid_init()) {
			//Serial.println("esp_bluedroid_init failed");
			return false;
		}
	}
	//Serial.println("esp_bluedroid_enable");
	if (bt_state != ESP_BLUEDROID_STATUS_ENABLED) {
		if (esp_bluedroid_enable()) {
			//Serial.println("esp_bluedroid_enable failed");
			return false;
		}
	}

	if (esp_ble_gap_config_adv_data_raw(eddystone_packet, eddystone_packet[7]+8)) {
		//Serial.println("gap_config_adv_data failed");
		return false;
	}

	esp_ble_gap_start_advertising(&_adv_params);
	return true;
}

bool NefryEddystone::end()
{
	if (btStarted()) {
		esp_bluedroid_disable();
		esp_bluedroid_deinit();
		btStop();
		return true;
	}
	return false;
}


bool NefryEddystone::setUrl(String url) {
	if (url.startsWith("http://www.")) {
		return setUrl(url.substring(11), 0);
	}
	else if (url.startsWith("https://www.")) {
		return setUrl(url.substring(12), 1);
	}
	else if (url.startsWith("http://")) {
		return setUrl(url.substring(7), 2);
	}
	else if (url.startsWith("https://")) {
		return setUrl(url.substring(8), 3);
	}
	else {
		return setUrl(url, 3);
	}
	return true;
}
bool NefryEddystone::setUrl(String url, int mode) {
	/** mode ˆø”î•ñ
	Decimal	Hex	Expansion
	0	0x00	http://www.
	1	0x01	https://www.
	2	0x02	http://
	3	0x03	https://
	*/
	eddystone_packet[13] = mode & 0xff;  // URL Scheme
	uint8_t uri_len = (uint8_t)url.length();
	if (uri_len >= 17)return false;
	for (int i = 0; i<uri_len; i++) {
		eddystone_packet[14 + i] = (uint8_t)url.charAt(i);
		//Serial.print(url.charAt(i));
	}
	eddystone_packet[7] = uri_len + 6;
}


#endif
