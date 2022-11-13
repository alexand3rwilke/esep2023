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



#define GPIO_PORT0 (uint64_t)0x44E07000
#define GPIO_REGISTER_LENGHT 0x1000
#define GPIO_DATAIN 0x138

// ADC Stuff
#define ADC_BASE 0x44E0D000
#define ADC_LENGTH 0x2000
#define ADC_DATA 0x100

#define BIT_MASK(x) (0x1 << (x))

uintptr_t gpioBase;
uintptr_t adcBaseAddr;

Sensor::Sensor() {

	ThreadCtl( _NTO_TCTL_IO, 0);
	gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);
	adcBaseAddr = mmap_device_io(ADC_LENGTH, ADC_BASE);

}

Sensor::~Sensor() {

}
 // mainLogik-->InterruptHandler--> Dispatcher --> Hal.readPin

	//Get value at pin x
int Sensor::getValueAtPin(int pin) {
	if(pin > 0  && pin < 32) {
		return current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;

	}
	// just read pins from 0-31, else out of range
	return 0;
}

uint32_t readHeight() {

	return in32((uintptr_t) adcBaseAddr + ADC_DATA);
}










