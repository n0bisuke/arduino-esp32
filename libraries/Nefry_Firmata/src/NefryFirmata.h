/*
 * NefryFirmata.h - Library for sending data to Ambient
 * Created by wami,1 9, 2016
 */
#ifndef NefryFirmata_h
#define NefryFirmata_h

#include "ConfigurableFirmata.h"
#include "utility/firmataDebug.h"

#define MAX_CONN_ATTEMPTS 20  // [500 ms] -> 10 s
#include <WiFi.h>
#include "utility/WiFiClientStream.h"
#include "utility/WiFiServerStream.h"
#include <Wire.h>
 // define your port number here, you will need this to open a TCP connection to your Arduino
#define NETWORK_PORT 3030

class NefryFirmata
{
public:

    NefryFirmata(void);
	bool begin();
    void loop();
   
private:
	void initFirmata();

};
void hostConnectionCallback(byte state);
void systemResetCallback();
#endif // NefryFirmata_h
