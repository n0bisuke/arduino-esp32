#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"

#include "./nefry/NefryWebServer.h"
#include "./nefry/Nefry.h"
#include "./nefry/NefryWiFi.h"
#include "./nefry/NefryConfig.h"
#include "./nefry/NefryConsole.h"
#include "./nefry/NefryUpdate.h"

#if CONFIG_AUTOSTART_ARDUINO

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

void loopTask(void *pvParameters)
{
	while (Nefry.getBootMode() == -1) {}
	while (Nefry.getBootMode() == 0) {
		Nefry.pollingSW();
	}
	if (Nefry.getWriteMode() != true) {
		delay(500);
		setup();
	}
	for(;;) {
        micros(); //update overflow
		if (Nefry.getWriteMode() != true) {
			loop();
		}
    }
}

void NefryBackEnd(void *pvParameters) {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	Nefry.nefry_init();
	NefryWeb.begin();
	NefryWiFi.beginWeb();
	NefryConfig.beginWeb();
	NefryWebServer.begin();
	NefryConsole.beginWeb();
	NefryUpdate.setupWebLocalUpdate();
	for (;;) {
		vTaskDelayUntil(&xLastWakeTime,10/portTICK_PERIOD_MS);
		NefryWeb.run();
		NefryWebServer.run();
		Nefry.pollingSW();
		Nefry.nefry_loop();
	}
}

extern "C" void app_main()
{
    initArduino();
	xTaskCreatePinnedToCore(loopTask,      "loopTask",     8192, NULL, 2, NULL,1);
	xTaskCreatePinnedToCore(&NefryBackEnd, "NefryBackEnd", 8192, NULL, 1, NULL,0);
}

#endif
