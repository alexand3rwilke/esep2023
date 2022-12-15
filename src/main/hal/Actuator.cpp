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




//uintptr_t gpio_bank_0;
//uintptr_t gpio_bank_1;
//uintptr_t gpio_bank_2;


Actuator::Actuator(Dispatcher *dispatcher) {

	disp = dispatcher;
	amp = new Amp();
	//ThreadCtl( _NTO_TCTL_IO, 0);

	gpio_bank_0 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO0_ADDRESS_START);
	gpio_bank_1 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO1_ADDRESS_START);
	gpio_bank_2 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO2_ADDRESS_START);

	assamblyMoveRightOff();
	assamblyMoveSlowOff();
	amp->ampOff();
	printf("Aktorik startz \n  ---- \n");
	int tmp = getAussortierer();


	cout << "\n Cout Aktorik\n" << endl;
	aktuatorThread = new thread([this]() {handleEvents();});

}

Actuator::~Actuator() {

}

void Actuator::handleEvents(void){


	int chanID = ChannelCreate(0);
	int ConID = ConnectAttach(0,0,chanID,_NTO_SIDE_CHANNEL,0);
	//printf("Aktorik conID: %d \n", ConID);
	actuatorEvents={START_FB, STOP_FB, MOVE_FASTER, MOVE_SLOWER, GREEN_ON, GREEN_OFF, YELLOW_ON, YELLOW_OFF, RED_ON, RED_OFF,ACTIVTE_AUSSORTIERER};


	disp->registerForEventWIthConnection(actuatorEvents, ConID);
	while(true){

		 int newPulse = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

//		 printf("in actuator thread");

		 switch(pulse.code){

			case START_FB: assamblyMoveRightOn();
			break;
			 case STOP_FB: assamblyMoveRightOff();
			break;
			case MOVE_FASTER: assamblyMoveSlowOff();
			break;
			case MOVE_SLOWER:assamblyMoveSlowOn();
			break;
			case GREEN_ON:amp->greenOn();
			break;
			case GREEN_OFF: amp->greenOff();
			break;
			case YELLOW_ON:amp->yellowOn();
			break;
			case YELLOW_OFF:amp->yellowOff();
			break;
			case RED_ON:amp->redOn();
			break;
			case RED_OFF:amp->redOn();
			break;
			case ACTIVTE_AUSSORTIERER:switchOn();
			break;

//			case GREEN_FLASCHING: amp->Ampel_Blinken(GRUEN, 1)
//			break;
		 }
	}


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



void Actuator::switchOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00080000);
	usleep(1000 * (2 * 1000 ));
	switchOff();
}

void Actuator::switchOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00080000);
}

void Actuator::ampOff(void) {
	amp->greenOff();
	amp->yellowOff();
	amp->redOff();
}

void Actuator::start_LedOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_2), (0x1 << 2));
}

void Actuator::start_LedOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_2), (0x1 << 2));
}

void Actuator::stop_LedOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_2), (0x1 << 3));
}

void Actuator::stop_LedOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_2), (0x1 << 2));
}

void Actuator::q1_LedOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_2), (0x1 << 4));
}

void Actuator::q1_LedOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_2), (0x1 << 2));
}

void Actuator::q2_LedOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_2), (0x1 << 5));
}

void Actuator::q2_LedOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_2), (0x1 << 2));
}

int Actuator::getAussortierer(void){

		 int tmp = in32((uintptr_t) (gpio_bank_1 + GPIO_DATAIN));
		 uint32_t bit = 14;
		 tmp = tmp & (1<<bit);
		 printf("/n Weichen wert: %d",tmp);
		 return tmp;
}



//
//void Actuator::startLED_ON(void){
//
//}
//void Actuator::startLED_OFF(void){
//
//}
//
//void Actuator::stopLED_ON(void){
//
//}
//void Actuator::stopLED_OFF(void){
//
//}
//void Actuator::q1LED_ON(void){
//
//}
//void Actuator::q1LED_OFF(void){
//
//}


