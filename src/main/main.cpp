/*
 * main.cpp
 *
 *  Created on: 25.10.2022
 *      Author: Alexander Wilke
 */

#ifndef RUN_TESTS

#include <iostream>
#include <stdio.h>
#include <iostream>
#include "hal/Actuator.h"
#include "hal/Sensor.h"
#include "ADC/ADC.h"
#include "ADC/TSCADC.h"

#include "ISR/ISR.h"
#include "Dispatcher/Dispatcher.h"

#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>





using namespace std;

void wait(int seconds) {

	usleep(1000 * (seconds * 1000 ));
}

int main(int argc, char** args) {

	cout << "Starting Festo Test" << endl;

	uintptr_t adcBaseAddr = mmap_device_io(ADC_LENGTH, ADC_BASE);
	bool aktorikDemo = false;


	// Händelt alle Evets
	Dispatcher dispatcher;

	// Muss keine Events verschicken, nur annehmen
	Actuator *actuator = new Actuator(&dispatcher);

	// Nur Events verschicken
	Sensor *sensor = new Sensor(&dispatcher);

	// Verschcikt nur events
	ISR *isr = new ISR(&dispatcher);

	// Init Höhenmesser
	TSCADC tscadc;
	ADC* adc = new ADC(tscadc); // ADC soll Events verschicken wenn Sample gemessen wurde


	// Sample misst das signal bei aufrud der methode
	 adc->sample();

	 // Lese höhe aus dem Register aus
	 uint32_t heightData =  in32((uintptr_t) adcBaseAddr + ADC_DATA);
	 printf("Value from adc with value %d!\n",heightData);


	 if(aktorikDemo){
		 // Move Assambly Left
		 	actuator->assamblyMoveLeftOn();
		 	wait(3);
		 	actuator->assamblyMoveLeftOff();

		 	// Move Assambly Right
		 	actuator->assamblyMoveRightOn();
		 	wait(3);
		 	actuator->assamblyMoveRightOff();

		 	// Move Assambly Slow
		 	actuator->assamblyMoveRightOn();
		 	actuator->assamblyMoveSlowOn();
		 	wait(3);
		 	actuator->assamblyMoveSlowOff();
		 	actuator->assamblyMoveRightOff();

		 	// Open Switch
		 	actuator->switchOn();
		 	wait(3);
		 	actuator->switchOff();

		 	// LED On
		 	actuator->redOn();
		 	actuator->yellowOn();
		 	actuator->greenOn();
		 	wait(3);
		 	actuator->redOff();
		 	actuator->yellowOff();
		 	actuator->greenOff();

	 }

	// Lese Interrupts aus und gebe auf pins aus
	while(true) {
		isr->handleInterrupt();
	}



	return EXIT_SUCCESS;
}




#endif