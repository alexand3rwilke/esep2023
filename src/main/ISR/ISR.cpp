
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

/* Interrupt numbers  (spruh73l.pdf S.465 ff.) */
#define INTR_GPIO_PORT0 97
#define INTR_GPIO_PORT1 99
#define INTR_GPIO_PORT2 33


/* GPIO port addresses (spruh73l.pdf S.177 ff.) */
#define GPIO_PORT0 0x44E07000
#define GPIO_PORT1 0x4804C000
#define GPIO_PORT2 0x481AC000


/* GPIO port registers length */
#define GPIO_REGISTER_LENGHT 0x1000


/* GPIO register offsets (spruh73l.pdf S.4877) */
#define GPIO_LEVELDETECT0 0x140
#define GPIO_LEVELDETECT1 0x144
#define GPIO_RISINGDETECT 0x148
#define GPIO_FALLINGDETECT 0x14C

#define GPIO_IRQSTATUS_0 0x2C
#define GPIO_IRQSTATUS_1 0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38

#define GPIO_DATAIN 0x138
#define GPIO_SETDATAOUT 0x194


// Lichtschranken
#define LIGHTBARRIER_FRONT_PIN 2	//active low
#define LIGHTBARRIER_BACK_PIN 20
#define LIGHTBARRIER_SLIDE_PIN 15


//Buttons
#define BUTTON_START_PIN 22			//active high
#define BUTTON_STOP_PIN 23
#define BUTTON_RESET_PIN 26
#define BUTTON_ESTOP_PIN 27

//Metall Detector
#define METALL_DET_PIN 7

#define ADC_DONE 21

/* Helper macros */
#define BIT_MASK(x) (0x1 << (x))


/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2


ISR::ISR() {

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
