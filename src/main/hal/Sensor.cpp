<<<<<<< HEAD
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


#define BIT_MASK(x) (0x1 << (x))

uintptr_t gpioBase;

Sensor::Sensor() {

	ThreadCtl( _NTO_TCTL_IO, 0);
	gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);

}

Sensor::~Sensor() {

}


	//Get value at pin x
int Sensor::getValueAtPin(int pin) {
	if(pin > 0  && pin < 32) {
		return current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;

	}
	return 0;
}










=======
/*
 * Sensor.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */

#include "Sensor.h"

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>


#define Sensor_ADDRESS_START (uint64_t)0x44E07000
#define Sensor_ADDRESS_LENGTH 0x1000
#define GPIO_READ_REGISTER(base) (uintptr_t)base + 0x138






uintptr_t gpio_bank_0;

Sensor::Sensor() {

	ThreadCtl( _NTO_TCTL_IO, 0);
	gpio_bank_0 = mmap_device_io(Sensor_ADDRESS_LENGTH, (uint64_t) Sensor_ADDRESS_START);

}

Sensor::~Sensor() {

}

// ASSAMBLY LINE
unsigned int  Sensor::getLSA1(void) {
	uint32_t inreg = in32(GPIO_READ_REGISTER(gpio_bank_0));
	unsigned int result = (inreg & 0x0000000F) << 2;
	//result = result & 0x0CD0C0BC;
	return result;


}













>>>>>>> development
