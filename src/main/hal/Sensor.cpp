
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
