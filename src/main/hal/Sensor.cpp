
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

#include <thread>
#include <chrono>


Sensor::Sensor(Dispatcher * dispatcher) {
	disp = dispatcher;
	dispID  = dispatcher->getConnectionID();
	SensorRoutineThread = new std::thread([this]() {sensorRoutine();});


}

Sensor::~Sensor() {

}

void Sensor::sensorRoutine() {


	// Hier signale weiterleiten

	//channel erstellen
	/* ### Create channel ### */
				int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
				if (chanID < 0) {
					perror("Could not create a channel!\n");

				}

				int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
				if (conID < 0) {
					perror("Could not connect to channel!");

				}


					_pulse pulse;

					// run 4ever
					 while (true) {

							int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

							   if (recvid < 0) {
							   			perror("MsgReceivePulse failed!");
							   			exit(EXIT_FAILURE);
							   		}

						 switch(pulse.code) {

						   case LSA1:
							   if (pulse.value.sival_int == 0) {
								   MsgSendPulse(dispID, -1, LSAnotInterrupted, 0);
								   break;
							   }	else {
								   MsgSendPulse(dispID, -1, LSAinterrupted, 0);
							   } break;

						 	// Do not ignore OS pulses!
					 }
}
}

 // mainLogik-->InterruptHandler--> Dispatcher --> Hal.readPin

	//Get value at pin x
