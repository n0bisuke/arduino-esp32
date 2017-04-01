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
	Nefry.nefry_init();
    setup();
	NefryWebServer.begin();
	for(;;) {
        loop();
		Nefry.nefry_loop();
    }
}

void Nefryserver(void *pvParameters) {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	for (;;) {
		vTaskDelayUntil(&xLastWakeTime,100/portTICK_PERIOD_MS);
		NefryWebServer.run();	
	}
}

extern "C" void app_main()
{
    initArduino();
    xTaskCreatePinnedToCore(loopTask, "loopTask", 4096, NULL, 2, NULL, ARDUINO_RUNNING_CORE);
	xTaskCreate(&Nefryserver, "NefryWeb", 4096, NULL, 1, NULL);
}

#endif
