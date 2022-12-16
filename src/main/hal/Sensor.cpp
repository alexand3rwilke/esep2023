
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
	dispID  = disp->getConnectionID();
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

				//Connect to channel
				int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0);
				if (conID < 0) {
					perror("Could not connect to channel!");
				}

				senorEvents={LSA1, LSE1, LSS1, HMS1, STR, ESTP, RST, STP, STR_SMZ};


				//printf("Sensorik conID: %d \n", conID);

				//senorEvents={LSA1, LSE1, LSS1, HMS1, SRT, ESTP, RST, STP};
				//nur zum Testen von Qnet m
				//senorEvents={LSA1, LSS1, HMS1, SRT, ESTP, RST, STP};


				disp->registerForEventWIthConnection(senorEvents, conID);

				_pulse pulse;

					// run 4ever
				while (true) {

					int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

					if (recvid < 0) {
							perror("MsgReceivePulse failed!");
							exit(EXIT_FAILURE);
					}
						// Untersuche und Sende event an Dispatcher
						 switch(pulse.code) {

						   case LSA1:
							   if (pulse.value.sival_int == 1) {
								   MsgSendPulse(dispID, -1, LSAnotInterrupted, 0);
								   break;
							   } else {
								   MsgSendPulse(dispID, -1, LSAinterrupted, 0);
							   } break;
						   case LSE1:
							   if (pulse.value.sival_int == 1) {
								   MsgSendPulse(dispID, -1, LSEnotInterrupted, 0);
								   break;
							   } else {
								   MsgSendPulse(dispID, -1, LSEinterrupted, 0);
							   } break;
						   case LSS1:
							   if (pulse.value.sival_int == 1) {
								   MsgSendPulse(dispID, -1, LSSnotInterrupted, 0);
								   break;
							   } else {
								   MsgSendPulse(dispID, -1, LSSinterrupted, 0);
							   } break;
						   case HMS1:
								   MsgSendPulse(dispID, -1, HMSinterrupted, 0);
							   break;


						   case STR:
							   printf("Sensro STR Taste -------- \n");
							   if (pulse.value.sival_int == 1) {
								   // Start timer
								   //Timer timer_SRT = new Timer();
							   } else {
								   // stop timer

								   MsgSendPulse(dispID, -1, STRinterrupted, 0);
							   }

							   break;
							case STP:

								if (pulse.value.sival_int == 0) {
									MsgSendPulse(dispID, -1, STPinterrupted, 0);
								}
								break;



							case ESTP:
							   if (pulse.value.sival_int == 1) {
								   MsgSendPulse(dispID, -1, ESTPnotInterrupted, 0);
								   break;
							   } else {
								   MsgSendPulse(dispID, -1, ESTPinterrupted, 0);
							   }
							   break;
						   case RST:
							   if (pulse.value.sival_int == 0) {
								   MsgSendPulse(dispID, -1, RSTinterrupted, 0);
							   }
							   break;
						   }

					 }
}
