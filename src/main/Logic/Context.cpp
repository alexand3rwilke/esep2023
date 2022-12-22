

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
		events = {LSA1interrupted,LSE1interrupted,STRinterrupted, STRnotInterrupted, STPinterrupted,
				LSS1interrupted, LSS1notInterrupted, LSE1notInterrupted,ADC_WK_IN_HM,ADC_WK_NIN_HM,STR_SMZ, MTD1interrupted,ADC_START_SINGLE_SAMPLE,
				ADC_SINGLE_SAMLING_FINISHED,ESTP1interrupted,ESTP1notInterrupted, RSTinterrupted,LSA2interrupted,LSE2interrupted,ESTP2interrupted,ESTP2notInterrupted
				LSR1notInterrupted,LSR2notInterrupted,LSR1interrupted,LSR2interrupted
				};

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
			   case ESTP1interrupted:
			 		state->doAction(ESTP1interrupted, msg);
			 		break;

			   case ESTP1notInterrupted:
			   		state->doAction(ESTP1notInterrupted, msg);
			   		break;


			   case ESTP2interrupted:
					state->doAction(ESTP2interrupted, msg);
					break;

			   case ESTP2notInterrupted:
					state->doAction(ESTP2notInterrupted, msg);
					break;



			   case RSTinterrupted:
			  		state->doAction(RSTinterrupted, msg);
			  		break;


			   	//----------------------------------------------------

			   case LSA1interrupted:
				   state->doAction(LSA1interrupted, msg);
				   break;

			   case LSE1interrupted:
				   state->doAction(LSE1interrupted, msg);
				   break;


			   case LSR1interrupted:
				   state->doAction(LSR1interrupted, msg);
				   break;

			   case	LSS1interrupted:
				   state->doAction(LSS1interrupted , msg);
				   break;

			   case LSE1notInterrupted:
				   state->doAction(LSE1notInterrupted, msg);
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
				   //state->doAction(STRinterrupted);

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

			  case MTD1interrupted:
				  state->doAction(MTD1interrupted, msg);
			   	   break;

			  case LSE2interrupted:
				  state->doAction(LSE2interrupted,msg);
				  break;
			  case LSA2interrupted:
				  state->doAction(LSA2interrupted,msg);
				  break;

				case LSR1notInterrupted:
				//TODO setze contextData Rampe1 voll auf false;
				break;

				case LSR2notInterrupted:
				//TODO setze contextData Rampe2 voll auf false;
				break;

				case LSR1interrupted : 
				//TODO setze contextData Rampe1 voll auf true;
				break;


				case LSR2interrupted : 
				//TODO setze contextData Rampe2 voll auf true;
				break;


				
			   }

		}
}
