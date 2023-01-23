

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
#include "../MQTTpublish/MQTTpublish/MQTTpublish.h"




Context::Context(Dispatcher *dispatcher, Actions *actions, ContextData  *contextData) {


	//TimerBZ timerBz;
//	TimerBZ timerBz;
//			timerBz = new TimerBZ(3,7);
	wkReihenfolgeIndex = 0;
	stateIndex = 0;
	this->contextData = contextData;
	this->disp = dispatcher;
	this->dispID = disp->getConnectionID();
	this->actions = actions;

	fisrsState = new RZ();
	fisrsState->setContextData(contextData);
	fisrsState->setActions(actions);
	//fisrsState->setZielWK(werkstuckReihenfolgeList.at(wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size()));
	//RZ
	fisrsState->setStateId(stateIndex);
	//contextData->setGescanntWKMapForStateForIndex(stateIndex,0,0);
	//contextData->setGesuchtWKMapForStateForIndex(stateIndex++,werkstuckReihenfolgeList.at(wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size()));

	fisrsState->entry();

	//cout << "GESUCHTES WK WURDE AUF FOLGENDES GESETZT: "<< contextData->getGesuchtWKMapForStateForIndex(/*fisrsState->getStateId()*/0) << "\n" << endl;
//	fisrsState->exit();
//
//	new (fisrsState) BZ;
//	fisrsState->entry();



	ContextThread = new std::thread([this]() {eventHandler();});
}

Context::~Context() {
	//delete states;
	ContextThread->join();
	delete fisrsState;
	delete disp;
	delete contextData;
	delete timerBz;
	delete actions;
}


void Context::eventHandler(){


		int chanID = ChannelCreate(0);
		fisrsState->setChannelId(chanID);
		if (chanID < 0) {
			perror("Could not create a channel!\n");
		}

		int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0);
		if (conID < 0) {
			perror("Could not connect to channel!");
		}

		events = 	{LSA1interrupted,LSA2interrupted,
					LSE1interrupted,LSE2interrupted,LSE1notInterrupted,LSE2notInterrupted,
					LSSinterrupted,LSS1notInterrupted,
					LSR1notInterrupted,LSR2notInterrupted,LSR1interrupted,LSR2interrupted,
					STRinterrupted,STRnotInterrupted,STPinterrupted,
					ADC_WK_IN_HM,ADC_WK_NIN_HM,ADC_SINGLE_SAMLING_FINISHED,ADC_START_SINGLE_SAMPLE,
					STR_SMZ,MTD1interrupted,
					ESTP1interrupted,ESTP1notInterrupted, 
					ESTP2interrupted,ESTP2notInterrupted,
					RSTinterrupted,
					WK_FLACH,WK_Normal,WK_Bohrung_Metal,WK_Bohrung,WK_UNDEFINED,
					WK_REMOVED,WK_ADDED,
					ESTP1Finished, ESTP2Finished,
					TIMER_IS_OVER,
					RUTSCHE_1_VOLL,RUTSCHE_2_VOLL,RUTSCHE_1_LEER,RUTSCHE_2_LEER,
					FA2_RUNNING,FA2_STOPPED, FEHLER_OK, FEHLER_1, FEHLER_2,
					DELETE_STATE

					};

		disp->registerForEventWIthConnection(events, conID);

			_pulse msg;

			while(true){

			int recvid = MsgReceivePulse(chanID, &msg, sizeof(_pulse), nullptr);

			   if (recvid < 0) {
			   			perror("MsgReceivePulse failed! - in Context");
			   			//exit(EXIT_FAILURE);
			   			//exit();
			   		}

			   switch(msg.code) {
			   case ESTP1interrupted:
				   fisrsState->doAction(ESTP1interrupted, msg);
			 		break;

			   case ESTP1notInterrupted:
			   		fisrsState->doAction(ESTP1notInterrupted, msg);
			   		break;


			   case ESTP2interrupted:
					fisrsState->doAction(ESTP2interrupted, msg);
					break;

			   case ESTP2notInterrupted:
					fisrsState->doAction(ESTP2notInterrupted, msg);
					break;

			   case ESTP1Finished:
				   fisrsState->doAction(ESTP1Finished, msg);
				   break;

			   case ESTP2Finished:
				   fisrsState->doAction(ESTP2Finished, msg);
				   break;


			   case RSTinterrupted:
			  		fisrsState->doAction(RSTinterrupted, msg);
			  		break;



			   case LSA1interrupted:
				   fisrsState->doAction(LSA1interrupted, msg);
				   break;

			   case LSE1interrupted:
			   contextData->setLs1Free(false);
				   fisrsState->doAction(LSE1interrupted, msg);
				   break;

			   case	LSSinterrupted:
				   fisrsState->doAction(LSSinterrupted , msg);
				   break;

			   case LSE1notInterrupted:
			   contextData->setLs1Free(true);
				   fisrsState->doAction(LSE1notInterrupted, msg);
				   break;


			   case LSE2notInterrupted:
				   fisrsState->doAction(LSE2notInterrupted, msg);
				   break;




			   case ADC_WK_IN_HM:

				   MsgSendPulse(chanID, -1, ADC_START_SINGLE_SAMPLE, 0);
				   fisrsState->doAction(ADC_WK_IN_HM, msg);
				   break;

			   case	ADC_WK_NIN_HM:

				   fisrsState->doAction(ADC_WK_NIN_HM, msg);
				   break;

			   case ADC_SINGLE_SAMLING_FINISHED:
				   cout << "ADC_SINGLE_SAMLING_FINISHED \n" << endl;
				   fisrsState->doAction(ADC_SINGLE_SAMLING_FINISHED, msg);
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

						if(time_diff >= 2){
							fisrsState->doAction(STR_SMZ ,msg);
							break;
						}else{
							fisrsState->doAction(STRinterrupted, msg);
							break;
						}
					}
				   break;

			  case STR_SMZ:
				  fisrsState->doAction(STR_SMZ, msg);
				  break;

			  case STPinterrupted:
				  fisrsState->doAction(STPinterrupted, msg);
				  break;

			  case MTD1interrupted:
				  fisrsState->doAction(MTD1interrupted, msg);
			   	   break;

			  case LSE2interrupted:
				  if(FESTO_TYPE == 2) {
					  actions->stopFB();
				  }
				  fisrsState->doAction(LSE2interrupted,msg);
				  break;

			  case LSA2interrupted:
				  fisrsState->doAction(LSA2interrupted,msg);
				  break;

				case LSR1notInterrupted:
				//cout << "Rutsche leer auf 1 --- vor Timer" << endl;
				fisrsState->doAction(LSR1interrupted, msg);
				timerBz = new TimerBZ(disp,2,LSR1notInterrupted, RUTSCHE_1_LEER);
				contextData->setRampe1Voll(false);
				break;

				case LSR2notInterrupted:
				//cout << "Rutsche leer auf 2--- vor Timer" << endl;
				fisrsState->doAction(LSR2interrupted, msg);
				timerBz = new TimerBZ(disp,2,LSR2notInterrupted, RUTSCHE_2_LEER);
				break;

				case LSR1interrupted : 
				//cout << "LSR1interrupted" << endl;
				timerBz = new TimerBZ(disp,2,LSR1notInterrupted,RUTSCHE_1_VOLL);
				fisrsState->doAction(LSR1interrupted, msg);
				break;



				case LSR2interrupted : 
				timerBz = new TimerBZ(disp,2,LSR2notInterrupted, RUTSCHE_2_VOLL);
				fisrsState->doAction(LSR2interrupted, msg);

				break;

				case RUTSCHE_1_VOLL:
				contextData->setRampe1Voll(true);
				fisrsState->doAction(RUTSCHE_1_VOLL, msg);
				break;

				case RUTSCHE_2_VOLL:

				fisrsState->doAction(RUTSCHE_2_VOLL, msg);
				break;

				case RUTSCHE_1_LEER:
					contextData->setRampe1Voll(false);
					fisrsState->doAction(RUTSCHE_1_LEER, msg);

					break;

				case RUTSCHE_2_LEER:
					contextData->setRampe2Voll(false);
					fisrsState->doAction(RUTSCHE_2_LEER, msg);
					break;



				case WK_ADDED :
				contextData->addWK();
				break;

				case WK_REMOVED :
				contextData->removeWK();
				break;

				case WK_FLACH :
				fisrsState->doAction(WK_FLACH, msg);
				break;

				case WK_Normal :
				fisrsState->doAction(WK_Normal, msg);
				break;

				case WK_Bohrung_Metal :
				fisrsState->doAction(WK_Bohrung_Metal, msg);
				break;

				case WK_Bohrung :
				fisrsState->doAction(WK_Bohrung, msg);
				break;

				case WK_UNDEFINED :
				fisrsState->doAction(WK_UNDEFINED, msg);
				break;

				case TIMER_IS_OVER:
				break;

				case FA2_RUNNING:
					contextData->setF2Running(true);


					break;
//				case FA2_STOPPED:
//					if(FESTO_TYPE == 1) {
//						cout << "LSE2 frei ist bei Festo 1 angegkommen" << endl;
//						if(contextData->getWKCount() >0) {
//							actions->startFB();
//						}
//					break;

				case FA2_STOPPED:
					contextData->setF2Running(false);
					if(contextData->getWKCount() >0 ) {
						//cout << "LSE2 frei ist bei Festo 1 angegkommen" << endl;
						actions->startFB();
					}
				break;

				case DELETE_STATE :
					fisrsState->doAction(DELETE_STATE, msg);
					break;

				default:
					fisrsState->doAction(msg.code, msg);
					break;
			   }
		}
}


