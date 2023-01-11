

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
#include "FZ/AnstehendQuittiert.h"

#include <stdio.h>
#include <iostream>


Context::Context(Dispatcher *dispatcher, Actions *actions, ContextData  *contextData) {

	// Setze state auf RZ
	state = new RZ();
	state->setContextData(contextData);
	state->setActions(actions);
	state->entry();

	disp = dispatcher;
	dispID = disp->getConnectionID();

	ContextThread = new std::thread([this]() {eventHandler();});
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
		events = {LSAinterrupted,LSEinterrupted,STRinterrupted, STRnotInterrupted, STPinterrupted,
				LSSinterrupted, LSR1interrupted, LSR2interrupted, ADC_WK_IN_HM,ADC_WK_NIN_HM,STR_SMZ, MTDinterrupted,
				ADC_START_SINGLE_SAMPLE, ADC_SINGLE_SAMLING_FINISHED, LSR1notInterrupted, LSR2notInterrupted,
				RU_VOLL, WSZuVielOderWSZuWenig};

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

			   //----------------------------------------------------
			   // EStop
			   case ESTPinterrupted:
			 		state->doAction(ESTPinterrupted, msg);
			 		break;

			   case ESTPnotInterrupted:
			   		state->doAction(ESTPnotInterrupted, msg);
			   		break;
			   case RSTinterrupted:
			  		state->doAction(RSTinterrupted, msg);
			  		break;


			   	//----------------------------------------------------

			   case LSAinterrupted:
				   //stateThreadsBZ.push_back();
					//bzThread = new std::thread([this]() {Context();});

				   state->doAction(LSAinterrupted, msg);
				   break;

			   case LSEinterrupted:
				   state->doAction(LSEinterrupted, msg);
				   break;


//			   case LSRinterrupted:
//				   state->doAction(LSRinterrupted, msg);
//				   break;

			   case	LSSinterrupted:
				   state->doAction(LSSinterrupted , msg);
				   break;

			   case LSEnotInterrupted:
				   state->doAction(LSEnotInterrupted, msg);
				   break;

			   case LSR1notInterrupted:
				   state->doAction(LSR1notInterrupted , msg);
				   break;

			   case LSR2notInterrupted:
				   state->doAction(LSR2notInterrupted , msg);
				   break;

			   case ADC_WK_IN_HM:
				   MsgSendPulse(chanID, -1, ADC_START_SINGLE_SAMPLE, 0);
				   state->doAction(ADC_WK_IN_HM, msg);
				   break;

			   case	ADC_WK_NIN_HM:
				   state->doAction(ADC_WK_NIN_HM, msg);
				   break;

			   case ADC_SINGLE_SAMLING_FINISHED:
				   state->doAction(ADC_SINGLE_SAMLING_FINISHED, msg);
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
							state->doAction(STR_SMZ ,msg);
							break;
						//Taster weniger als 2 Sekunden, dann BZ
						}else{
							state->doAction(STRinterrupted, msg);
							break;
						}
					}
				   break;

			  case STR_SMZ:
				  state->doAction(STR_SMZ, msg);
				  break;

			  case STPinterrupted:
				  // if keine Warning
				  state->doAction(STPinterrupted, msg);
				  break;

			  case MTDinterrupted:
				  state->doAction(MTDinterrupted, msg);
			   	   break;

			  case RU_VOLL:
				  state->doAction(RU_VOLL, msg);
				  break;

			  case WSZuVielOderWSZuWenig:
				  state->doAction(WSZuVielOderWSZuWenig,msg);
				  break;

			  default:
				  state->doAction(msg.code,msg);
			   }
		}
}

//void Context::eventHandlerBZ(){
//
//
//}
