/*
* Sensor.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 *
 */
#include "Sensor.h"

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

#define BIT_MASK(x) (0x1 << (x))

uintptr_t gpioBase;

Sensor::Sensor(Dispatcher * dispatcher) {

	ThreadCtl( _NTO_TCTL_IO, 0);
	gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
}

Sensor::~Sensor() {

}
 // mainLogik-->InterruptHandler--> Dispatcher --> Hal.readPin

	//Get value at pin x
int Sensor::getValueAtPin(int pin) {
	if(pin > 0  && pin < 32) {
		return (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;

	}
	// just read pins from 0-31, else out of range
	return 0;
}
<<<<<<< HEAD


=======
>>>>>>> aa97bcff3895cee9b7e7d7fd0c7c218067f53c71

