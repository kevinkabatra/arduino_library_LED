#include "Arduino.h"
#include "LED.h"

LED::LED(String description, int digitalPin, bool isLEDLit, long LEDBlinkSpeed) {
	_description = description;
	_digitalPin  = digitalPin;
	_LEDBlinkSpeed = LEDBlinkSpeed;
	
	pinMode(_digitalPin, OUTPUT);
	init(isLEDLit, _LEDBlinkSpeed);
}

/*
	See also: https://www.arduino.cc/reference/en/language/structure/pointer-access-operators/reference/
*/
void LED::init(bool& isLEDLit, long LEDBlinkSpeed) {
	isLEDLit ? SetLEDOn() : SetLEDOff();
	_CyclesTilLEDBlink = LEDBlinkSpeed;
}

String LED::GetLEDDescription() {
	return _description;
}

long LED::GetLEDBlinkSpeed() {
	return _LEDBlinkSpeed;
}

int LED::GetLEDDigitalPin() {
	return _digitalPin;
}

bool LED::GetLEDState() {
	return digitalRead(_digitalPin);
}

bool LED::SetLEDOff() {
	digitalWrite(_digitalPin, LOW);
	return GetLEDState();
}

bool LED::SetLEDOn() {
	digitalWrite(_digitalPin, HIGH);
	return GetLEDState();
}

bool LED::ToggleLED() {
	bool currentLEDState = GetLEDState();
	
	if(currentLEDState) {
		SetLEDOff();
	}
	else {
		SetLEDOn();
	}

	return currentLEDState != GetLEDState() ? true : false;
}

long LED::UpdateCyclesTilLEDBlink() {
	Serial.println(_CyclesTilLEDBlink);

	if(_CyclesTilLEDBlink == 0) {
		_CyclesTilLEDBlink = _LEDBlinkSpeed;
	}
	else {
		_CyclesTilLEDBlink--;
	}
	
	return _CyclesTilLEDBlink;
}