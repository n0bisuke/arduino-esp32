// Nefry Beacon
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

#ifndef _NEFRY_BEACON_H_
#define _NEFRY_BEACON_H_

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

class NefryBeacon {
    public:
        /**
         * Start BLE Advertising
         *
         * @param[in] uuid  UUID
         * @param[in] major  major
         * @param[in] minor  minor
         *
         * @return true on success
         *
         */
        bool begin(uint8_t uuid[16], uint16_t major, uint16_t minor);

        /**
         * Stop BLE Advertising
         *
         * @return none
         */
        bool end(void);
};

#endif

#endif
