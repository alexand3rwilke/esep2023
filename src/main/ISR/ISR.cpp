
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


ISR::ISR(Dispatcher *dispatcher) {

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
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(LIGHTBARRIER_FRONT_PIN));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(LIGHTBARRIER_BACK_PIN));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(LIGHTBARRIER_SLIDE_PIN));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(BUTTON_START_PIN));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(BUTTON_STOP_PIN));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(BUTTON_RESET_PIN));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(BUTTON_ESTOP_PIN));
			out32((uintptr_t) port0BaseAddr + GPIO_IRQSTATUS_SET_1, BIT_MASK(METALL_DET_PIN));


			// Set irq event types.
			unsigned int temp;

				// Lichtschranke Ausgang
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(LIGHTBARRIER_BACK_PIN) | BIT_MASK(LIGHTBARRIER_BACK_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

				//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(LIGHTBARRIER_BACK_PIN) | BIT_MASK(LIGHTBARRIER_BACK_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


				// Lichtschranke Eingang
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(LIGHTBARRIER_FRONT_PIN) | BIT_MASK(LIGHTBARRIER_FRONT_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

				//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(LIGHTBARRIER_FRONT_PIN) | BIT_MASK(LIGHTBARRIER_FRONT_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


				 //Lichtschranke Rampe
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(LIGHTBARRIER_SLIDE_PIN) | BIT_MASK(LIGHTBARRIER_SLIDE_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

				//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(LIGHTBARRIER_SLIDE_PIN) | BIT_MASK(LIGHTBARRIER_SLIDE_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


				// Sensor Metall Detector
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(METALL_DET_PIN) | BIT_MASK(METALL_DET_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

				//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(METALL_DET_PIN) | BIT_MASK(METALL_DET_PIN));//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.



				// BUTTONS


				//Reset Button
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_RESET_PIN) | BIT_MASK(BUTTON_RESET_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

				//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_RESET_PIN) | BIT_MASK(BUTTON_RESET_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


				// ESTOP Button
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_ESTOP_PIN) | BIT_MASK(BUTTON_ESTOP_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

				//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_ESTOP_PIN) | BIT_MASK(BUTTON_ESTOP_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.

				// BUTTON_STOP_PIN
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_STOP_PIN) | BIT_MASK(BUTTON_STOP_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

				//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_STOP_PIN) | BIT_MASK(BUTTON_STOP_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.


				// Start Button
				//	Rising Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_START_PIN) | BIT_MASK(BUTTON_START_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_RISINGDETECT), temp);			//Write new config back.

								//	Falling Edge
				temp = in32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT));			//Read current config.
				temp |= (BIT_MASK(BUTTON_START_PIN) | BIT_MASK(BUTTON_START_PIN));		//Add desired pins.
				out32((uintptr_t) (port0BaseAddr + GPIO_FALLINGDETECT), temp);			//Write new config back.




			/* ### Start thread for handling interrupt messages. */
			//thread receivingThread = thread(&receivingRoutine, chanID);
}
 // mainLogik-->InterruptHandler--> Dispatcher --> Hal.readPin

	//Get value at pin x
void ISR::handleInterrupt(void) {

	//printf("Im in handle interrupt");
	uintptr_t gpioBase = mmap_device_io(GPIO_REGISTER_LENGHT, GPIO_PORT0);

	unsigned int intrStatusReg = in32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1));

	out32(uintptr_t(gpioBase + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
	//InterruptUnmask(INTR_GPIO_PORT0, interruptID);				//unmask interrupt.

	for (int pin = 0; pin < 32; pin++) {
		unsigned int mask = (uint32_t) BIT_MASK(pin);
		if (intrStatusReg == mask) {
			int current_level = (in32((uintptr_t) gpioBase + GPIO_DATAIN) >> pin) & 0x1;
			printf("Interrupt on pin %d, now %d\n", pin, current_level);
		}
	}
}
