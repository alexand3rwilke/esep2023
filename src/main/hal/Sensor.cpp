
/*
 * Sensor.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 *
 */
#include "Sensor.h"
#include "../Imports.h"

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

	senorEvents={LSA, LSE, LSS, HMS, STR, ESTP, RST, STP, STR_SMZ, MTD};

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

			   case LSA:
				   if (pulse.value.sival_int == 1) {
					   MsgSendPulse(dispID, -1, LSA1notInterrupted, 0);
					   break;
				   } else {

					   if(FESTO_TYPE == 1) {

						   MsgSendPulse(dispID, -1, LSA1interrupted, 0);
						   printf("Festo 1 LSA interrupt");
						   printf("%d",FESTO_TYPE);

					   } else  if(FESTO_TYPE == 2) {
						   	   printf("Festo 2 LSA interrupt");
						   	 printf("%d",FESTO_TYPE);
						   MsgSendPulse(dispID, -1, LSA2interrupted, 0);
					   }

				   } break;
			   case LSE:
				   if (pulse.value.sival_int == 1) {



					   	   	  if(FESTO_TYPE == 1) {
						    MsgSendPulse(dispID, -1, LSE1notInterrupted, 0);
					   } else if(FESTO_TYPE == 2) {

						   MsgSendPulse(dispID, -1, LSE2notInterrupted, 0);
					   }
					 


					   break;
				   } else {
					   if(FESTO_TYPE == 1) {
						   MsgSendPulse(dispID, -1, LSE1interrupted, 0);
						   cout << "\n  Sensorik sagt: LSE1interrupted auf FBM1\n" << endl;
					   } else if(FESTO_TYPE == 2) {

						   cout << "\n  Sensorik sagt: LSE1interrupted auf FBM2\n" << endl;

						   MsgSendPulse(dispID, -1, LSE2interrupted, 0);
					   }


				   } break;
			   case LSS:
				   if (pulse.value.sival_int == 1) {
					   MsgSendPulse(dispID, -1, LSS1notInterrupted, 0);
					   break;
				   } else {
					   MsgSendPulse(dispID, -1, LSS1interrupted, 0);
				   } break;
			   case LSR:
				   if (pulse.value.sival_int == 1) {

					if(FESTO_TYPE == 1) {
						   MsgSendPulse(dispID, -1, LSR1notInterrupted, 0);
					   } else if(FESTO_TYPE == 2) {

						  MsgSendPulse(dispID, -1, LSR2notInterrupted, 0);
					   }
					   break;
					   
				   } else {
					if(FESTO_TYPE == 1) {
						   MsgSendPulse(dispID, -1, LSR1interrupted, 0);
					   } else if(FESTO_TYPE == 2) {

						  MsgSendPulse(dispID, -1, LSR2interrupted, 0);
					   }
				   } break;
			   case HMS:
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
					   cout << "ESTP ist druaßen\n" << endl;

 						if(FESTO_TYPE == 1) {
						    MsgSendPulse(dispID, -1, ESTP1notInterrupted, 0);
					   } else if(FESTO_TYPE == 2) {

						  MsgSendPulse(dispID, -1, ESTP2notInterrupted, 0);
					   }
					   break;
				   } else {
					   cout << "ESTP Reingedrückt\n" << endl;
					   if(FESTO_TYPE == 1) {
						     MsgSendPulse(dispID, -1, ESTP1interrupted, 0);
					   } else if(FESTO_TYPE == 2) {

						   MsgSendPulse(dispID, -1, ESTP2interrupted, 0);
					   }

				   }
				   break;
			   case RST:
				   if (pulse.value.sival_int == 0) {
					   MsgSendPulse(dispID, -1, RSTinterrupted, 0);
				   }
				   break;
			   case MTD:
				   MsgSendPulse(dispID, -1, MTD1interrupted, 0);
			   }

		 }
}
