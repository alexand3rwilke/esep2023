
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

	//channel erstellen
	int chanID = ChannelCreate(0);
	if (chanID < 0) {
		perror("Could not create a channel!\n");
	}

	//Connect to channel
	int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0);
	if (conID < 0) {
		perror("Could not connect to channel!");
	}

	senorEvents={LSA1, LSE1, LSS1, HMS1, STR, ESTP, RST, STP, STR_SMZ};

	//nur zum Testen von Qnet m
	//senorEvents={LSA1, LSS1, HMS1, SRT, ESTP, RST, STP};

	disp->registerForEventWIthConnection(senorEvents, conID);

	_pulse pulse;
	//TODO Estop vor dem Start
		// run 4ever
	while (true) {

		int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

		if (recvid < 0) {
				perror("MsgReceivePulse failed!- in Sensorik");
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
			   case LSR1:
				   if (pulse.value.sival_int == 1) {
					   MsgSendPulse(dispID, -1, LSRnotInterrupted, 0);
					   break;
				   } else {
					   MsgSendPulse(dispID, -1, LSRinterrupted, 0);
				   } break;
			   case HMS1:
					   MsgSendPulse(dispID, -1, HMSinterrupted, 0);
				   break;
			   case STR:
				   if (pulse.value.sival_int == 1) {
					   MsgSendPulse(dispID, -1, STRinterrupted, 0);
				   } else {
					   MsgSendPulse(dispID, -1, STRnotInterrupted, 0);
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
			   case MTD1:
				   MsgSendPulse(dispID, -1, MTDinterrupted, 0);
			   }

		 }
//=======
//						// Untersuche und Sende event an Dispatcher
//						 switch(pulse.code) {
//
//						   case LSA1:
//							   if (pulse.value.sival_int == 1) {
//								   MsgSendPulse(dispID, -1, LSAnotInterrupted, 0);
//								   break;
//							   } else {
//								   MsgSendPulse(dispID, -1, LSAinterrupted, 0);
//							   } break;
//						   case LSE1:
//							   if (pulse.value.sival_int == 1) {
//								   MsgSendPulse(dispID, -1, LSEnotInterrupted, 0);
//								   break;
//							   } else {
//								   MsgSendPulse(dispID, -1, LSEinterrupted, 0);
//							   } break;
//						   case LSS1:
//							   if (pulse.value.sival_int == 1) {
//								   MsgSendPulse(dispID, -1, LSSnotInterrupted, 0);
//								   break;
//							   } else {
//								   MsgSendPulse(dispID, -1, LSSinterrupted, 0);
//							   } break;
//						   case HMS1:
//								   MsgSendPulse(dispID, -1, HMSinterrupted, 0);
//							   break;
//
//
//						   case STR:
//							   printf("STR Taste --------Sensorik \n");
//							   if (pulse.value.sival_int == 1) {
//								   MsgSendPulse(dispID, -1, STRinterrupted, 0);
//							   } else {
//								   MsgSendPulse(dispID, -1, STRnotInterrupted, 0);
//							   }
//							   break;
//							case STP:
//
//								if (pulse.value.sival_int == 0) {
//									MsgSendPulse(dispID, -1, STPinterrupted, 0);
//								}
//								break;
//
//
//
//							case ESTP:
//							   if (pulse.value.sival_int == 1) {
//								   MsgSendPulse(dispID, -1, ESTPnotInterrupted, 0);
//								   break;
//							   } else {
//								   MsgSendPulse(dispID, -1, ESTPinterrupted, 0);
//							   }
//							   break;
//						   case RST:
//							   if (pulse.value.sival_int == 0) {
//								   MsgSendPulse(dispID, -1, RSTinterrupted, 0);
//							   }
//							   break;
//						   }
//
//					 }
//>>>>>>> dev
}
