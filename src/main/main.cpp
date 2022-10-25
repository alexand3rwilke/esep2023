/*
 * main.cpp
 *
 *  Created on: 25.10.2022
 *      Author: Alexander Wilke
 */

#ifndef RUN_TESTS

#include <iostream>
#include "hal/Actuator.h"


using namespace std;

void wait(int seconds) {

	usleep(1000 * (seconds * 1000 ));
}

int main(int argc, char** args) {

	cout << "Starting Festo Test" << endl;

	// Init Actuator
	Actuator a;

	// Move Assambly Left
	a.assamblyMoveLeftOn();
	wait(3);
	a.assamblyMoveLeftOff();

	// Move Assambly Right
	a.assamblyMoveRightOn();
	wait(3);
	a.assamblyMoveRightOff();

	// Move Assambly Slow
	a.assamblyMoveLeftOn();
	a.assamblyMoveSlowOn();
	wait(3);
	a.assamblyMoveSlowOff();
	a.assamblyMoveLeftOff();

	// Open Switch
	a.switchOn();
	wait(3);
	a.switchOff();

	// LED On
	a.redOn();
	a.yellowOn();
	a.greenOn();
	wait(3);
	a.redOff();
	a.yellowOff();
	a.greenOff();

	return EXIT_SUCCESS;
}

#endif
