/*
 * main.cpp
 *
 *  Created on: 25.10.2022
 *      Author: Alexander Wilke
 */

#ifndef RUN_TESTS

#include <iostream>
#include "hal/Actuator.h"
#include <stdio.h>
#include <iostream>
#include "hal/Sensor.h"


using namespace std;

void wait(int seconds) {

	usleep(1000 * (seconds * 1000 ));
}

int main(int argc, char** args) {

	cout << "Starting Festo Test" << endl;

	// Init Actuator
	Actuator a;
	Sensor s;

	unsigned int test = s.getLSA1();
	cout << test << endl;

//	 Move Assambly Left
//	a.assamblyMoveLeftOn();
//	wait(3);
//	a.assamblyMoveLeftOff();

	// Move Assambly Right
//	a.assamblyMoveRightOn();
//	wait(3);
//	a.assamblyMoveRightOff();
//
//	// Move Assambly Slow
//	a.assamblyMoveRightOn();
//	a.assamblyMoveSlowOn();
//	wait(3);
//	a.assamblyMoveSlowOff();
//	a.assamblyMoveRightOff();
//
//	// Open Switch
//	a.switchOn();
//	wait(3);
//	a.switchOff();
//
//	// LED On
//	a.redOn();
//	a.yellowOn();
//	a.greenOn();
//	wait(3);
//	a.redOff();
//	a.yellowOff();
//	a.greenOff();

	// Read Sensorpins 0-31
	for (int pin = 0; pin < 32; pin++) {
			int outputPin = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;
			printf("Value on pin %d is %d\n", pin, outputPin);
		}

	return EXIT_SUCCESS;
}

#endif
