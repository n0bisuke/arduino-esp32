#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"

#include "./nefry/NefryWebServer.h"
#include "./nefry/Nefry.h"

#if CONFIG_AUTOSTART_ARDUINO

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

void loopTask(void *pvParameters)
{
	Serial.println("Nefrybackend");
	while (Nefry.getBootMode() == 0) {
		Serial.print(".");
	}
	if (Nefry.getWriteMode() != true) {
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
	NefryWebServer.begin();
	for (;;) {
		vTaskDelayUntil(&xLastWakeTime,100/portTICK_PERIOD_MS);
		NefryWeb.run();
		NefryWebServer.run();	
		Nefry.pollingSW();
		Nefry.nefry_loop();
	}
}

extern "C" void app_main()
{
    initArduino();
	xTaskCreatePinnedToCore(loopTask, "loopTask", 4096, NULL, 2, NULL, 1);
	xTaskCreatePinnedToCore(&NefryBackEnd, "NefryBackEnd", 9192, NULL, 1, NULL,0);
}

#endif
