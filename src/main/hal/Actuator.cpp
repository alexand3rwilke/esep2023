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


uintptr_t gpio_bank_0;
uintptr_t gpio_bank_1;
uintptr_t gpio_bank_2;




Actuator::Actuator(Dispatcher *dispatcher) {
	gpio_bank_0 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO0_ADDRESS_START);
	gpio_bank_1 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO1_ADDRESS_START);
	gpio_bank_2 = mmap_device_io(GPIO1_ADDRESS_LENGTH, (uint64_t) GPIO2_ADDRESS_START);



	disp = dispatcher;
	amp = new Amp();
	//ThreadCtl( _NTO_TCTL_IO, 0);
	FB_stop();
	FB_moveSlowOff();
	amp->ampOff();
	q1_LedOff();
	q2_LedOff();
	start_LedOn();
	stop_LedOff();

	istWeiche = getAussortierer();


	cout << "\n Cout Aktorik\n" << endl;
	aktuatorThread = new thread([this]() {handleEvents();});


}

Actuator::~Actuator() {
}

void Actuator::handleEvents(void){

	int chanID = ChannelCreate(0);
	int ConID = ConnectAttach(0,0,chanID,_NTO_SIDE_CHANNEL,0);

	actuatorEvents={START_FB, STOP_FB, MOVE_FASTER, MOVE_SLOWER, GREEN_ON, GREEN_OFF, YELLOW_ON,
			YELLOW_OFF, RED_ON, RED_OFF,WS_DURCHLASSEN,WS_DURCHLASSEN,ESTPinterrupted, Q1On, Q2On, Q1Off, Q2Off, GREEN_BLINKING_ON,
			RED_BLINKING_ON,YELLOW_BLINKING_ON};

	disp->registerForEventWIthConnection(actuatorEvents, ConID);
	while(true){

		 int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);
		 if (recvid < 0) {
		 							perror("MsgReceivePulse failed!- in Actuator");
		 							exit(EXIT_FAILURE);
		 					}

		 switch(pulse.code){

			case START_FB: FB_start();
			break;

			 case STOP_FB: FB_stop();
			break;

			case MOVE_FASTER: FB_moveSlowOff();
			break;

			case MOVE_SLOWER:FB_moveSlowOn();
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

			case RED_OFF:amp->redOff();
			break;

			case ESTPinterrupted:
			break;

			case GREEN_BLINKING_ON:	amp->flashinLight(GREEN,1);
			break;

			case YELLOW_BLINKING_ON: amp->flashinLight(YELLOW,1);
			break;

			case RED_BLINKING_ON: amp->flashinLight(RED,1);
			break;

			case WS_DURCHLASSEN:durchlassen();
			break;

			case Q1On:q1_LedOn();
			break;

			case Q2On:q2_LedOn();
			break;

			case Q1Off:q1_LedOff();
			break;

			case Q2Off:q2_LedOff();
			break;

		 }
	}
}

// ASSAMBLY LINE
void Actuator::FB_start(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00001000);
}

void Actuator::FB_stop(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00001000);
}

//void Actuator::assamblyMoveLeftOn(void) {
//	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00002000);
//}
//
//void Actuator::assamblyMoveLeftOff(void) {
//	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00002000);
//}

void Actuator::FB_moveSlowOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00004000);

}

void Actuator::FB_moveSlowOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00004000);
}


void Actuator::assamblyStopOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00008000);
}

void Actuator::assamblyStopOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00008000);
}

void Actuator::durchlassen(void) {
	if(istWeiche==0){
		out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00080000);
			usleep(1000 * (1 * 1000 ));
			//weiche wieder zu machen
			out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00080000);
	}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00080000);
}

void Actuator::aussortieren(void) {
	if(istWeiche!=0){
			out32(GPIO_SET_REGISTER(gpio_bank_1), 0x00080000);
				usleep(1000 * (1 * 1000 ));
				//Auswerfer zruückfahren
				out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00080000);
	}
	out32(GPIO_CLEAR_REGISTER(gpio_bank_1), 0x00080000);
}

void Actuator::estp(void) {
	FB_stop();
	amp->ampOff();
	amp->flashinLight(RED,1);
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
	//out32(GPIO_CLEAR_REGISTER(gpio_bank_2), (0x1 << 2));
	out32((uintptr_t) (gpio_bank_2 + 0x190), 1 << 4);
}

void Actuator::q2_LedOn(void) {
	out32(GPIO_SET_REGISTER(gpio_bank_2), (0x1 << 5));
}

void Actuator::q2_LedOff(void) {
	out32(GPIO_CLEAR_REGISTER(gpio_bank_2), (0x1 << 2));
}

int Actuator::getAussortierer(void){

		int tmp = in32((uintptr_t) (gpio_bank_0 + 0x138));
		 uint32_t bit = 14;
		 tmp = tmp & (1<<bit);
		 printf(" Weichen wert: %d",tmp);
		 return tmp;
}

int Actuator::getSorter(){
	return istWeiche;
}





