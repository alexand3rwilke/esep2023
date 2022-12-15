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
					Rot_BlinkenT->join();
				}

	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00010000);
}

void Amp::redOff(void) {
	if (redIsFlashing) {
					redIsFlashing = false;
					Rot_BlinkenT->join();
				}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00010000);
}

void Amp::yellowOn(void) {
	if (yellowIsFlashing) {
		yellowIsFlashing = false;
		Gelb_BlinkenT->join();
	}
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00020000);
}

void Amp::yellowOff(void) {
	if (yellowIsFlashing) {
		yellowIsFlashing = false;
		Gelb_BlinkenT->join();
	}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00020000);
}

void Amp::greenOn(void) {
	if (greenIsFlashing) {
		greenIsFlashing = false;
		Gruen_BlinkenT->join();
	}
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00040000);
}

void Amp::greenOff(void) {
	if (greenIsFlashing) {
		greenIsFlashing = false;
		Gruen_BlinkenT->join();
	}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00040000);
}





void Amp::StartRotBlinken(int hz) {

	while(redIsFlashing) {
		out32((uintptr_t) (gpio_bank_1 + 0x194), 1 << 16);
		usleep(hz*300000);
		out32((uintptr_t) (gpio_bank_1 + 0x190), 1 << 16);
		usleep(hz*300000);
	}
}

void Amp::StartGelbBlinken(int hz) {

	while(yellowIsFlashing) {
		out32((uintptr_t) (gpio_bank_1 + 0x194), 1 << 17);
		usleep(hz*300000);
		out32((uintptr_t) (gpio_bank_1 + 0x190), 1 << 17);
		usleep(hz*300000);
	}
}

void Amp::StartGruenBlinken(int hz) {

	while(greenIsFlashing) {
		out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00040000);
		usleep(hz*300000);
		out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00040000);
		usleep(hz*300000);
	}
}

void Amp::Ampel_Blinken(Farbe farbe, int hz) {
	switch(farbe)
	{
	case ROT:
		if(!redIsFlashing)
		{
			redIsFlashing = true;
			Rot_BlinkenT = new std::thread([this, hz]() {StartRotBlinken(hz);});
		}
		break;
	case GELB:
		if(!yellowIsFlashing)
		{
			yellowIsFlashing = true;
			Gelb_BlinkenT = new std::thread([this, hz]() {StartGelbBlinken(hz);});
		}
		break;
	case GRUEN:
		if(!greenIsFlashing)
		{
			greenIsFlashing = true;
			Gruen_BlinkenT = new std::thread([this, hz]() {StartGruenBlinken(hz);});
		}
		break;
	default: std::cout << "Amepl blinken bekam eine falsche Farbe" << std::endl;
	}
}


void Amp::ampOff(void){
	greenOff();
	yellowOff();
	redOff();
}




