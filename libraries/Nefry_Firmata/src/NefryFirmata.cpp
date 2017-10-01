/*
 * NefryFirmata.cpp - Library for sending data to Ambient
 * Created by Takehiko Shimojima, April 21, 2016
 */
#include "NefryFirmata.h"

WiFiServerStream stream(NETWORK_PORT);

#include <DigitalInputFirmata.h>
DigitalInputFirmata digitalInput;

#include <DigitalOutputFirmata.h>
DigitalOutputFirmata digitalOutput;

#include <AnalogInputFirmata.h>
AnalogInputFirmata analogInput;

// analogWrite not supported for ESP32 boards
#ifndef ESP32
#include <AnalogOutputFirmata.h>
AnalogOutputFirmata analogOutput;
#endif

// servo not supported for ESP32 boards
#ifndef ESP32
#include <Servo.h>
#include <ServoFirmata.h>
ServoFirmata servo;
#endif
// ServoFirmata depends on AnalogOutputFirmata
#if defined ServoFirmata_h && ! defined AnalogOutputFirmata_h
#error AnalogOutputFirmata must be included to use ServoFirmata
#endif

#include <Wire.h>
#include <I2CFirmata.h>
I2CFirmata i2c;

#include <OneWireFirmata.h>
OneWireFirmata oneWire;

#include <StepperFirmata.h>
StepperFirmata stepper;

#include <SerialFirmata.h>
SerialFirmata serial;

#include <FirmataExt.h>
FirmataExt firmataExt;

#include <FirmataScheduler.h>
FirmataScheduler scheduler;

/*===================================================================================
* END FEATURE CONFIGURATION - you should not need to change anything below this line
*==================================================================================*/

// dependencies. Do not comment out the following lines
#if defined AnalogOutputFirmata_h || defined ServoFirmata_h
#include <AnalogWrite.h>
#endif

#if defined AnalogInputFirmata_h || defined I2CFirmata_h || defined FirmataEncoder_h
#include <FirmataReporting.h>
FirmataReporting reporting;
#endif

int connectionAttempts = 0;
bool streamConnected = false;

/*==============================================================================
* FUNCTIONS
*============================================================================*/

void systemResetCallback()
{
	// initialize a default state

	// pins with analog capability default to analog input
	// otherwise, pins default to digital output
	for (byte i = 0; i < TOTAL_PINS; i++) {
		if (IS_PIN_ANALOG(i)) {
#ifdef AnalogInputFirmata_h
			// turns off pull-up, configures everything
			Firmata.setPinMode(i, PIN_MODE_ANALOG);
#endif
		}
		else if (IS_PIN_DIGITAL(i)) {
#ifdef DigitalOutputFirmata_h
			// sets the output to 0, configures portConfigInputs
			Firmata.setPinMode(i, OUTPUT);
#endif
		}
	}

#ifdef FirmataExt_h
	firmataExt.reset();
#endif
}

/*
* Called when a TCP connection is either connected or disconnected.
* TODO:
* - report connected or reconnected state to host (to be added to protocol)
*/
void hostConnectionCallback(byte state)
{
	switch (state) {
	case HOST_CONNECTION_CONNECTED:
		DEBUG_PRINTLN("TCP connection established");
		break;
	case HOST_CONNECTION_DISCONNECTED:
		DEBUG_PRINTLN("TCP connection disconnected");
		break;
	}
}
void NefryFirmata::initFirmata()
{
	stream.attach(hostConnectionCallback);
	Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);

#ifdef FirmataExt_h
#ifdef DigitalInputFirmata_h
	firmataExt.addFeature(digitalInput);
#endif
#ifdef DigitalOutputFirmata_h
	firmataExt.addFeature(digitalOutput);
#endif
#ifdef AnalogInputFirmata_h
	firmataExt.addFeature(analogInput);
#endif
#ifdef AnalogOutputFirmata_h
	firmataExt.addFeature(analogOutput);
#endif
#ifdef ServoFirmata_h
	firmataExt.addFeature(servo);
#endif
#ifdef I2CFirmata_h
	firmataExt.addFeature(i2c);
#endif
#ifdef OneWireFirmata_h
	firmataExt.addFeature(oneWire);
#endif
#ifdef StepperFirmata_h
	firmataExt.addFeature(stepper);
#endif
#ifdef SerialFirmata_h
	firmataExt.addFeature(serial);
#endif
#ifdef FirmataReporting_h
	firmataExt.addFeature(reporting);
#endif
#ifdef FirmataScheduler_h
	firmataExt.addFeature(scheduler);
#endif
#ifdef FirmataEncoder_h
	firmataExt.addFeature(encoder);
#endif
#endif
	/* systemResetCallback is declared here (in ConfigurableFirmata.ino) */
	Firmata.attach(SYSTEM_RESET, systemResetCallback);


	// Initialize Firmata to use the WiFi stream object as the transport.
	Firmata.begin(stream);
	systemResetCallback();  // reset to default config
}

void NefryFirmata::loop()
{
#ifdef DigitalInputFirmata_h
	/* DIGITALREAD - as fast as possible, check for changes and output them to the
	* stream buffer using Firmata.write()  */
	digitalInput.report();
#endif

	/* STREAMREAD - processing incoming message as soon as possible, while still
	* checking digital inputs.  */
	while (Firmata.available()) {
		Firmata.processInput();
#ifdef FirmataScheduler_h
		if (!Firmata.isParsingMessage()) {
			goto runtasks;
		}
	}
	if (!Firmata.isParsingMessage()) {
	runtasks: scheduler.runTasks();
#endif
	}

	// TODO - ensure that Stream buffer doesn't go over 60 bytes

#ifdef FirmataReporting_h
	if (reporting.elapsed()) {
#ifdef AnalogInputFirmata_h
		/* ANALOGREAD - do all analogReads() at the configured sampling interval */
		analogInput.report();
#endif
#ifdef I2CFirmata_h
		// report i2c data for all device with read continuous mode enabled
		i2c.report();
#endif
#ifdef FirmataEncoder_h
		// report encoders positions if reporting enabled.
		encoder.report();
#endif
	}
#endif
#ifdef StepperFirmata_h
	stepper.update();
#endif
#ifdef SerialFirmata_h
	serial.update();
#endif

	// keep the WiFi connection live. Attempts to reconnect automatically if disconnected.
	stream.maintain();
}

NefryFirmata::NefryFirmata() {
}
bool NefryFirmata::begin()
{
	initFirmata();
	return true;
}
