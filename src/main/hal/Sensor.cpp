
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
	dispId  = dispatcher->getConnectionID();
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

						 	 //
						 int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

//						 switch(pulse.code) {
//
//						 	   case INT_LS_AUS:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, WK_AUS_NDURCH, 0);
//						 		   break;
//
//						 	   case INT_LS_EIN:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, WK_EIN_DURCH, 0);
//						 		   break;
//
//						 	   case INT_LS_HOE:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, WK_HE_DURCH, 0);
//						 		   break;
//
//						 	   case	INT_LS_RMP:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, WK_RMP_DURCH, 0);
//						 		   break;
//
//						 	   case	INT_LS_WEI:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, WK_WEI_DURCH, 0);
//						 			   break;
//
//						 	   case	INT_LS_MET:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, WK_METAL, 0);
//						 			   break;
//
//						 	   case	INT_T_EST:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, T_EST_GDR, 0);
//						 			   break;
//
//						 	   case INT_T_RES:
//						 			  MsgSendPulse(disp->conIDDispatcher, -1, T_RES_NGDR, 0);
//						 			  break;
//
//						 	   case INT_T_STP:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, T_STP_GDR, 0);
//						 			   break;
//
//						 	   case INT_T_STR:
//						 			   MsgSendPulse(disp->conIDDispatcher, -1, T_STR_NGDR, 0);
//						 			   break;
//						 	   }
//
//						 	 // switch case here
//
//						 			// Do not ignore OS pulses!
					 }


}

 // mainLogik-->InterruptHandler--> Dispatcher --> Hal.readPin

	//Get value at pin x
