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




uintptr_t gpio_bank_1;

Actuator::Actuator(Dispatcher *dispatcher) {

	disp = dispatcher;
	//ThreadCtl( _NTO_TCTL_IO, 0);
	gpio_bank_1 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO1_ADDRESS_START);
	aktuatorThread = new thread([this]() {handleEvents();});



}

Actuator::~Actuator() {

}

void Actuator::handleEvents(void){


	int chanID = ChannelCreate(0);
	int ConID = ConnectAttach(0,0,chanID,_NTO_SIDE_CHANNEL,0);
	actuatorEvents={START_FB, STOP_FB, MOVE_FASTER, MOVE_SLOWER, GREEN_ON, GREEN_OFF, YELLOW_ON, YELLOW_OFF, RED_ON, RED_OFF};

	disp->registerForEventWIthConnection(actuatorEvents, ConID);
	while(true){
		 int newPulse = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);
		 	printf("in actuator thread");
		 switch(pulse.code){
			 case START_FB: assamblyMoveRightOn();
			 break;
			 case STOP_FB: assamblyMoveRightOff();
			break;
			case MOVE_FASTER: assamblyMoveSlowOff();
			break;
			case MOVE_SLOWER:assamblyMoveSlowOn();
			break;
			case GREEN_ON:greenOn();
			break;
			case GREEN_OFF: greenOff();
			break;
			case YELLOW_ON:yellowOn();
			break;
			case YELLOW_OFF:yellowOff();
			break;
			case RED_ON:redOn();
			break;
			case RED_OFF: redOn();
			break;
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


