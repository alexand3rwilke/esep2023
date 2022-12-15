/*
 * Amp.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Jobut
 */

#include "Amp.h"



Amp::Amp() {
	redIsFlashing = false;
	yellowIsFlashing = false;
	greenIsFlashing = false;
	gpio_bank_1 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO1_ADDRESS_START);


}

Amp::~Amp() {

}


void Amp::redOn(void) {
	if (redIsFlashing) {
			redIsFlashing = false;
			red_thread->join();
		}
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00010000);
}

void Amp::redOff(void) {
	if (redIsFlashing) {
			redIsFlashing = false;
			red_thread->join();
		}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00010000);
}

void Amp::yellowOn(void) {
	if (yellowIsFlashing) {
		yellowIsFlashing = false;
		yellow_thread->join();
	}
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00020000);
}

void Amp::yellowOff(void) {
	if (yellowIsFlashing) {
		yellowIsFlashing = false;
		yellow_thread->join();
	}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00020000);
}

void Amp::greenOn(void) {
	if (greenIsFlashing) {
		greenIsFlashing = false;
		green_thread->join();
	}
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00040000);
}

void Amp::greenOff(void) {
	if (greenIsFlashing) {
		greenIsFlashing = false;
		green_thread->join();
	}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00040000);
}





void Amp::redFlashing(int hz) {
	while(redIsFlashing) {
		out32((uintptr_t) (gpio_bank_1 + 0x194), 1 << 16);
		usleep(hz*300000);
		out32((uintptr_t) (gpio_bank_1 + 0x190), 1 << 16);
		usleep(hz*300000);
	}
}

void Amp::yellowFlashing(int hz) {
	while(yellowIsFlashing) {
		out32((uintptr_t) (gpio_bank_1 + 0x194), 1 << 17);
		usleep(hz*300000);
		out32((uintptr_t) (gpio_bank_1 + 0x190), 1 << 17);
		usleep(hz*300000);
	}
}

void Amp::greenFlashing(int hz) {
	while(greenIsFlashing) {
		out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00040000);
		usleep(hz*300000);
		out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00040000);
		usleep(hz*300000);
	}
}

void Amp::flashinLight(TrafficColer coler, int hz) {
	switch(coler){
	case RED:
		if(!redIsFlashing){
			redIsFlashing = true;
			red_thread = new std::thread([this, hz]() {redFlashing(hz);});
		}
		break;
	case YELLOW:
		if(!yellowIsFlashing){
			yellowIsFlashing = true;
			yellow_thread = new std::thread([this, hz]() {yellowFlashing(hz);});
		}
		break;
	case GREEN:
		if(!greenIsFlashing){
			greenIsFlashing = true;
			green_thread = new std::thread([this, hz]() {greenFlashing(hz);});
		}
		break;
	}
}


void Amp::ampOff(void){
	greenOff();
	yellowOff();
	redOff();
}




