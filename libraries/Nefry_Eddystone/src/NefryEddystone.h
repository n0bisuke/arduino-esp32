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


#ifndef _NEFRY_EDDYSTONE_H_
#define _NEFRY_EDDYSTONE_H_

#include "sdkconfig.h"

#if defined(CONFIG_BT_ENABLED) && defined(CONFIG_BLUEDROID_ENABLED)

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bt.h"

#include "Arduino.h"

struct ble_gap_adv_params_s;

class NefryEddystone {
    public:
        /**
         * Start BLE Advertising
         *
         * @param[in] url URL
         *
         * @return true on success
         *
         */
        bool begin(String url);

        /**
         * Stop BLE Advertising
         *
         * @return none
         */
        bool end(void);

    private:
		bool setUrl(String url);

		bool setUrl(String url, int mode);
    private:

};

#endif

#endif
