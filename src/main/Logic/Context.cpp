

/*
 * Context.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "Context.h"
#include "ContextData.h"
#include "Basestate.h"

#include "RZ/RZ.h"
#include "BZ/BZ.h"
#include "ESZ/ESz.h"
#include "SMZ/SMZ.h"
#include "FZ/FZ.h"

#include <stdio.h>
#include <iostream>


Context::Context(Dispatcher *dispatcher, Actions *actions, ContextData  *contextData) {

	// Setze state auf RZ
	state = new RZ();
	disp = dispatcher;
	dispID = disp->getConnectionID();
	state->setContextData(contextData);
	state->setActions(actions);
	ContextThread = new std::thread([this]() {eventHandler();});

	state->entry();
}

Context::~Context() {
	delete state;
	delete disp;
}


void Context::eventHandler(){

	/* ### Create channel ### */
		int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
		if (chanID < 0) {
			perror("Could not create a channel!\n");
		}

		int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
		if (conID < 0) {
			perror("Could not connect to channel!");
		}
		//TODO alle sensorsignale einfügen
		events = {LSAinterrupted,LSEinterrupted,STRinterrupted, STRnotInterrupted, STPinterrupted,LSSinterrupted,ADC_WK_IN_HM,ADC_WK_NIN_HM,STR_SMZ};

		disp->registerForEventWIthConnection(events, conID);

			_pulse msg;
			//Verschicke events an den aktuellen State
			while(true){

			int recvid = MsgReceivePulse(chanID, &msg, sizeof(_pulse), nullptr);

			   if (recvid < 0) {
			   			perror("MsgReceivePulse failed! - in Context");
			   			//exit(EXIT_FAILURE);
			   			//exit();
			   		}


			   switch(msg.code) {

			   case LSAinterrupted:
				   state->doAction(LSAinterrupted);
				   break;

			   case LSEinterrupted:
				   state->doAction(LSEinterrupted);
				   break;

			   case ADC_WK_IN_HM:
				   state->doAction(ADC_WK_IN_HM);
				   break;

			   case	ADC_WK_NIN_HM:
				   state->doAction(ADC_WK_NIN_HM);
				   break;

			   case	STRinterrupted:
					time_t start_time;
					time_t end_time;
					start_time = time(NULL);

					//Schaue ob BZ oder SMZ
					while(true){
						MsgReceivePulse(chanID, &msg, sizeof(_pulse), nullptr);
						end_time = time(NULL);
						double time_diff = difftime(end_time,start_time);

						//Taster länger als 2 Sekunden betätigt, dann SMZ
						if(time_diff >= 2){
							state->doAction(STR_SMZ);
							break;
						//Taster weniger als 2 Sekunden, dann BZ
						}else{
							state->doAction(STRinterrupted);
							break;
						}
					}
				   break;

			   case	LSSinterrupted:
				   state->doAction(LSSinterrupted);
				   break;

			  case STR_SMZ:
				  state->doAction(STR_SMZ);
				  break;

			  case STPinterrupted:
				  // if keine Warning
				  state->doAction(STPinterrupted);
			   }

		}
}

//			 * Hier wird die Taste Start geprüft, on die lange gedrückt oder schnell gedrückt
//							 * Zeit: 2 Sekunden
//							 * >= : Kalibierung
//							 * < : Betriebzuistand
//							 */
//							if (recvid == 0) {	//pulse received.
//								if(msg.code == T_STR_GDR || msg.code == FBM2_STR_GDR){
//

//
//									while(true) {
//										int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);
//
//
//										if (msg.code == T_STR_NGDR || msg.code == FBM2_STR_NGDR) {
//
//											end_time = time(NULL);
//
//											double time_diff = difftime(end_time,start_time);
//
//											if(time_diff >= 2){
//												new(this) KalibrierungIdle;
//												 entry();
//
//											}
//		}
