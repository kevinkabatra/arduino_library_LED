/*
	Arduino library that will support physical Light Emitting Diodes (LEDs).
*/

#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED {
	public:
		/* Constructor */
		LED(String description, int digitalPin, bool isLEDLit, long LEDBlinkSpeed);
		
		void   init(bool& isLEDLit, long LEDBlinkSpeed);
		long   GetLEDBlinkSpeed();
		String GetLEDDescription();
		int    GetLEDDigitalPin();
		bool   GetLEDState();
		bool   SetLEDOff();		
		bool   SetLEDOn();		
		bool   ToggleLED();
		long   UpdateCyclesTilLEDBlink();

	private:
		String _description;
		int    _digitalPin;
		bool   _isLEDLit;
		long    _LEDBlinkSpeed; //this corresponds to the clock on the Arduino
		long   _CyclesTilLEDBlink;
};

#endif