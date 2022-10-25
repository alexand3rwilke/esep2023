/*
 * Actuator.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */

#include "Actuator.h"

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>


#define GPIO1_ADDRESS_START (uint64_t)0x4804C000
#define GPIO1_ADDRESS_LENGTH 0x1000
#define GPIO_SET_REGISTER(base) (uintptr_t)base + 0x194
#define GPIO_CLEAR_REGISTER(base) (uintptr_t)base + 0x190


uintptr_t gpio_bank_1;

Actuator::Actuator() {

	ThreadCtl( _NTO_TCTL_IO, 0);
	gpio_bank_1 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO1_ADDRESS_START);

}

Actuator::~Actuator() {

}

// ASSAMBLY LINE
void Actuator::assamblyMoveRightOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00001000);
}

void Actuator::assamblyMoveRightOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00001000);
}

void Actuator::assamblyMoveLeftOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00002000);
}

void Actuator::assamblyMoveLeftOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00002000);
}

void Actuator::assamblyMoveSlowOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00004000);
}

void Actuator::assamblyMoveSlowOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00004000);
}


void Actuator::assamblyStopOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00008000);
}

void Actuator::assamblyStopOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00008000);
}

void Actuator::redOn(void) {

	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00010000);
}

void Actuator::redOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00010000);
}

void Actuator::yellowOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00020000);
}

void Actuator::yellowOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00020000);
}

void Actuator::greenOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00040000);
}

void Actuator::greenOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00040000);
}

void Actuator::switchOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00080000);
}

void Actuator::switchOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00080000);
}










