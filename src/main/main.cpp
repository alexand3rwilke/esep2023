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

	// Init Actuator
	Actuator a;
	Sensor s;
	ISR isr;
	TSCADC tscadc;
	ADC* adc = new ADC(tscadc);


	// Sample misst das signal bei aufrud der methode
	 adc->sample();

	 // Lese höhe aus dem Register aus
	 uint32_t heightData =  in32((uintptr_t) adcBaseAddr + ADC_DATA);
	 printf("Value from adc with value %d!\n",heightData);


	 if(aktorikDemo){
		 // Move Assambly Left
		 	a.assamblyMoveLeftOn();
		 	wait(3);
		 	a.assamblyMoveLeftOff();

		 	// Move Assambly Right
		 	a.assamblyMoveRightOn();
		 	wait(3);
		 	a.assamblyMoveRightOff();

		 	// Move Assambly Slow
		 	a.assamblyMoveRightOn();
		 	a.assamblyMoveSlowOn();
		 	wait(3);
		 	a.assamblyMoveSlowOff();
		 	a.assamblyMoveRightOff();

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

	 }

	// Lese Interrupts aus und gebe auf pins aus
	while(true) {
		isr.handleInterrupt();
	}



	return EXIT_SUCCESS;
}




#endif
