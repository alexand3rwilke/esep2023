
/*
 * ISR.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 *
 */
#include "ISR.h"

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

#include <errno.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>


// TODO : Alle defines und includes in eine grosse header file



/* Helper macros */
#define BIT_MASK(x) (0x1 << (x))



/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2

//ISR::ISR(Sensor *sensor) {
//	dispId  = sensorik->getConnectionID();

ISR::ISR(Dispatcher *dispatcher) {

	dispId  = dispatcher->getConnectionID();
	ISRRoutineThread  = new std::thread([this]() {recieveInterruptRoutine();});

}

ISR::~ISR() {


}

void ISR::recieveInterruptRoutine() {

	ThreadCtl(_NTO_TCTL_IO, 0);
	InterruptEnable();
	int interruptID;

	/* ### Create channel ### */
			int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
			if (chanID < 0) {
				perror("Could not create a channel!\n");

			}

			int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
			if (conID < 0) {
				perror("Could not connect to channel!");

			}



			/* ### Register interrupts by OS. ### */
			struct sigevent intr_event;
			SIGEV_PULSE_INIT(&intr_event, conID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
			interruptID = InterruptAttachEvent(INTR_GPIO_PORT0, &intr_event, 0);
			if (interruptID < 0) {
				perror("Interrupt was not able to be attached!");

			}

			/* ### Configure registers to receive irq events. */
			uintptr_t port0BaseAddr = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);


			// Enable interrupts on pins.
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(LSA));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(LSE));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(LSR));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(STR));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(STP));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(RST));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(ESTP));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(MTD));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(LSS));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(HMS));




			// Set irq event types.
			unsigned int temp;

			// Lichtschranke Ausgang
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSE) | BIT_MASK(LSE));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSE) | BIT_MASK(LSE));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


			// Lichtschranke Eingang
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSA) | BIT_MASK(LSA));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSA) | BIT_MASK(LSA));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


			 //Lichtschranke Rampe
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSR) | BIT_MASK(LSR));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSR) | BIT_MASK(LSR));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.

			// NEW
			 //Lichtschranke Am Sortierer
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSS) | BIT_MASK(LSS));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(LSS) | BIT_MASK(LSS));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


			// Sensor Metall Detector
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(MTD) | BIT_MASK(MTD));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(MTD) | BIT_MASK(MTD));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


			// WS in Höhenmesser
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(HMS) | BIT_MASK(HMS));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(HMS) | BIT_MASK(HMS));//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.



			//Reset Button
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(RST) | BIT_MASK(RST));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(RST) | BIT_MASK(RST));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


			// ESTOP Button
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(ESTP) | BIT_MASK(ESTP));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(ESTP) | BIT_MASK(ESTP));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.

			// STP
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(STP) | BIT_MASK(STP));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

			//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(STP) | BIT_MASK(STP));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


			// Start Button
			//	Rising Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
			temp |= (BIT_MASK(STR) | BIT_MASK(STR));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

							//	Falling Edge
			temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
			temp |= (BIT_MASK(STR) | BIT_MASK(STR));		//Add desired pins.
			out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.





			_pulse pulse;

				// run 4ever
				 while (true) {

					 	 //
					 int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

					 		if (recvid < 0) {
					 			perror("MsgReceivePulse failed! - in ISR");
					 			exit(EXIT_FAILURE);
					 		}

					 		if (pulse.code == PULSE_INTR_ON_PORT0){
					 			handleInterruptAndSend(interruptID);
					 			//	cout <<"Message send! \n"<<endl;

					 					}


					 			// Do not ignore OS pulses!
				 }

			/* ### Start thread for handling interrupt messages. */
			//thread receivingThread = thread(&receivingRoutine, chanID);
}
 // mainLogik-->InterruptHandler--> Dispatcher --> Hal.readPin

	//Get value at pin x
void ISR::handleInterruptAndSend(int interruptID) {

	//printf("Im in handle interrupt");
	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);

	unsigned int intrStatusReg = in32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1));

	out32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
	InterruptUnmask(INTR_GPIO_PORT0, interruptID);				//delete interrupt.

	for (int pin = 0; pin < 32; pin++) {
		unsigned int mask = (uint32_t) BIT_MASK(pin);
		if (intrStatusReg == mask) {
			int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;

			//printf("Interrupt on pin %d, now %d\n", pin, current_level);


				switch(pin) {

				case ESTP :
					MsgSendPulse(dispId, -1, ESTP,current_level);
					break;

				case LSA : MsgSendPulse(dispId, -1, LSA,current_level);
				break;

				case LSE : MsgSendPulse(dispId, -1, LSE,current_level);
				break;

				case LSS : MsgSendPulse(dispId, -1, LSS,current_level);
				break;

				case LSR: MsgSendPulse(dispId, -1, LSR,current_level);
				break;

				case STR : MsgSendPulse(dispId, -1, STR,current_level);
				break;

				case RST: MsgSendPulse(dispId, -1, RST,current_level);
				break;

				case STP: MsgSendPulse(dispId, -1, STP,current_level);
				break;

				case MTD:MsgSendPulse(dispId, -1, MTD,current_level);
				break;

				}
			}
		}
	}

