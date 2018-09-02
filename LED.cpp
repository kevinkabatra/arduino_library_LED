/**
 * @Purpose
 * 	Arduino library that will support physical Light Emitting Diodes (LEDs).
 * 
 * @Description
 * 	Each instance of an LED contains:
 * 	1. a human readable description, which can be used for debugging or 
 *     other reporting purposes,
 *  2. a digital pin that the button will send its input to,
 *  3. and a boolean that represents if the bulb is currently lit.
 *
 * I have also authored a timer library, 
 * see https://github.com/kevinkabatra/arduino_library_timer,
 * and I use that to control the blinking of my LEDs.
 * 
 * @Example
 * 	//Construct the timer for the LED blinking
 * 	Timer ledBlinkTimer(millis(), Timer::TimeUnit::Second, 1, true);
 * 
 * 	//Constuct a single LED
 * 	LED player1StartLED("Player 1 Start", 8 , false);
 * 
 * 	//Construct multiple LEDs
 * 	const short numberOfLEDs = 4;
 *	LED leds[numberOfLEDs] = {
 * 		LED("Player 1 Start", 8 , false),
 * 		LED("Player 2 Start", 9 , false),
 * 		LED("Player 1 Coin" , 10, false),
 * 		LED("Player 2 Coin" , 11, false)  
 * 	}
 * 
 * 	//Set the coin LEDs to be on, this is during setup
 * 	leds[2].SetLEDOn();
 * 	leds[3].SetLEDOn();
 * 
 *  //Blink the LEDs, this is done in the `loop`
 *  ledBlinkTimer.UpdateTimer();
 * 	if(ledBlinkTimer.isTimerExpired) {
 * 		leds[0].ToggleLED(); 
 * 		leds[1].ToggleLED();
 * 		ledBlinkTimer.ResetTimer();
 * 	}
 * 
 * @LICENSE 
 *   MIT License
 *   Copyright (c) 2018 Kevin Kabatra
 * 
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 * 
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 * 
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
*/

#include "Arduino.h"
#include "LED.h"

/**
 * Constructor for a Light Emitting Diode (LED).
 * 
 * @param description String representing a human readable name or description
 *  of the physical button. This is usefull for debugging or other reporting
 *  purposes.
 * @param digitalPin Byte representing the physical digital pin location on the
 *  Arduino that this button's input is sent to.
 * @param isLEDLit Boolean representing if the LED's bulb is currently on.
 */
LED::LED(
	String description, 
	byte digitalPin, 
	bool isLEDLit
) {
	SetDescription(description);
	SetDigitalPin(digitalPin);  
	init(isLEDLit);
}

/**
 * Gets the human readable description assigned to this LED.
 * 
 * @return String representing a human readable name or description
 *  of the physical LED. This is usefull for debugging or other reporting
 *  purposes.
 */
String LED::GetDescription() {
  return _description;
}
/**
 * Sets the description for this LED.
 * 
 * @param description String representing a human readable name or description
 *  of the physical LED. This is usefull for debugging or other reporting
 *  purposes.
 */
void LED::SetDescription(String& description) {
  _description = description;
}

/**
 * Gets the digital pin assigned to this LED.
 * 
 * @return Byte representing the physical digital pin location on the
 *  Arduino that this LED's input is sent to.
 */
byte LED::GetDigitalPin() {
  return _digitalPin;
}
/**
 * Sets the digital pin for this LED.
 * 
 * @param digitalPin Byte representing the physical digital pin location on the
 *  Arduino that this LED's input is sent to.
 */
void LED::SetDigitalPin(byte& digitalPin) {
  _digitalPin = digitalPin;
  pinMode(_digitalPin, OUTPUT);
}

/**
 *  Initializes the LED.
 */
void LED::init(bool& isLEDLit) {
	isLEDLit ? SetOn() : SetOff();
}

/**
 * Gets the current state of the of the LED's bulb.
 * 
 * @param Boolean representing the current state of the LED's bulb.
 */
bool LED::GetState() {
	return digitalRead(_digitalPin);
}

/**
 * Sets the LED's bulb to be off.
 * 
 * @return Boolean representing the state of the LED's bulb
 * 	after the function is run, this can be used to validate
 * 	that the change was successful.
 */
bool LED::SetOff() {
	digitalWrite(_digitalPin, LOW);
	return GetState();
}

/**
 * Sets the LED's bulb to be on.
 * 
 * @return Boolean representing the state of the LED's bulb
 * 	after the function is run, this can be used to validate
 * 	that the change was successful.
 */
bool LED::SetOn() {
	digitalWrite(_digitalPin, HIGH);
	return GetState();
}

/**
 * Toggles the LED's current state.
 * 
 * @return Boolean representing the state of the LED's bulb
 * 	after the function is run, this can be used to validate
 * 	that the change was successful.
 */
bool LED::Toggle() {
	return GetState() ? SetOff() : SetOn();
}