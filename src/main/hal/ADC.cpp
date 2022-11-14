
/*
 * ADC.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 *
 */
#include "ADC.h"

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

uintptr_t adcBaseAddr;

ADC::ADC() {

	ThreadCtl( _NTO_TCTL_IO, 0);
	adcBaseAddr = mmap_device_io(ADC_LENGTH, ADC_BASE);

}

ADC::~ADC() {

}
 // mainLogik-->InterruptHandler--> Dispatcher --> Hal.readPin

	//Get value at pin x

uint32_t ADC::readHeight() {

	return in32((uintptr_t) adcBaseAddr + ADC_DATA);
}
