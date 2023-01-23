

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
	// Setze State auf RZ

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
//	fisrsState->entry(); //TODO ---------------------------------------------------------------------------------------- Nur für den Test



	ContextThread = new std::thread([this]() {eventHandler();});
}

Context::~Context() {
	//delete states;

	delete fisrsState;
	delete disp;
	delete contextData;
}


void Context::eventHandler(){

	/* ### Create channel ### */
		int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
		fisrsState->setChannelId(chanID);
		if (chanID < 0) {
			perror("Could not create a channel!\n");
		}

		int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
		if (conID < 0) {
			perror("Could not connect to channel!");
		}
		//TODO alle sensorsignale einfügen
		events = 	{LSA1interrupted,LSA2interrupted,
					LSE1interrupted,LSE2interrupted,LSE1notInterrupted,LSE2notInterrupted,
					LSS1interrupted,LSS1notInterrupted,
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
			//Verschicke events an den aktuellen State
			while(true){

			int recvid = MsgReceivePulse(chanID, &msg, sizeof(_pulse), nullptr);

			   if (recvid < 0) {
			   			perror("MsgReceivePulse failed! - in Context");
			   			//exit(EXIT_FAILURE);
			   			//exit();
			   		}

			   //for(Basestate *state : stateList) {



			   switch(msg.code) {
			   //----------------------------------------------------
			   // EStop
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


			   	//----------------------------------------------------

			   case LSA1interrupted:
					   // ADD NEW STATE
					   // TODO hier noch unterscheiden ob wir im fisrsState sind, um nich am Anfang schon mit 2 states zu starten
					   // Da-> init mit [fisrsState] in RZ(), dann kommt LSA1 interrupted welches nicht einen neuen State in den vector packen soll...
//					  if(!fisrsState) {
//				   	   Basestate *newState = new BZ;
//					   newState->setContextData(contextData);
//					   newState->setActions(actions);
//					   newState->entry();
//					   newState->doAction(LSA1interrupted, msg);
//					   // setze gesuchtes WK auf den aktuellen stand der liste und setze den pointer danach hoch
//					   //newState->setZielWK(werkstuckReihenfolgeList.at(wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size()));
//					   newState->setStateId(stateIndex);
//					   contextData->setGescanntWKMapForStateForIndex(stateIndex,0);
//					   contextData->setGesuchtWKMapForStateForIndex(stateIndex++,wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size());
//					   stateList.push_back(newState);
//					   fisrsState = false;
//					   contextData->addWK();
//					   cout << "WK anzahl auf den FB ist : " << contextData->getWKCount();
//					  }

				   	// danach normale action
				   fisrsState->doAction(LSA1interrupted, msg);

				   break;

			   case LSE1interrupted:
				   fisrsState->doAction(LSE1interrupted, msg);
				   break;

			   case	LSS1interrupted:
				   fisrsState->doAction(LSS1interrupted , msg);
				   break;

			   case LSE1notInterrupted:
				   fisrsState->doAction(LSE1notInterrupted, msg);
				   break;


			   case LSE2notInterrupted:
				   fisrsState->doAction(LSE2notInterrupted, msg);
				   break;




			   case ADC_WK_IN_HM:
				   //cout << "ADC_WK_IN_HM \n" << endl;

				   MsgSendPulse(chanID, -1, ADC_START_SINGLE_SAMPLE, 0);
				   fisrsState->doAction(ADC_WK_IN_HM, msg);
				   break;

			   case	ADC_WK_NIN_HM:
				   //cout << "ADC_WK_NIN_HM \n" << endl;

				   fisrsState->doAction(ADC_WK_NIN_HM, msg);
				   break;

			   case ADC_SINGLE_SAMLING_FINISHED:
				   cout << "ADC_SINGLE_SAMLING_FINISHED \n" << endl;
				   fisrsState->doAction(ADC_SINGLE_SAMLING_FINISHED, msg);
				   break;

			   case	STRinterrupted:


				  				  	//mqtt->sendToConsole("Start Mqtt");
				   //state->doAction(STRinterrupted);
//				   contextData->setMqtt("Hallo STR");
//				   MsgSendPulse(dispID,-1,MQTTMESSAGE,0);
				   //MQTTPublish *mqtt = new  MQTTPublish(&dispatcher,contextData,"MQTT in Context start");
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
							fisrsState->doAction(STR_SMZ ,msg);
							break;
						//Taster weniger als 2 Sekunden, dann BZ
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
//				  MQTTPublish *mqtt_j = new  MQTTPublish(contextData->disp,contextData);

				  //mqtt->sendToConsole("SToppp Mqtt");
				  // if keine Warning
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
				cout << "Rutsche leer auf 1 --- vor Timer" << endl;
				fisrsState->doAction(LSR1interrupted, msg);
				timerBz = new TimerBZ(disp,3,LSR1notInterrupted, RUTSCHE_1_LEER);
				contextData->setRampe1Voll(false);
				//TODO setze contextData Rampe1 voll auf false;
				break;

				case LSR2notInterrupted:
				cout << "Rutsche leer auf 2--- vor Timer" << endl;
				fisrsState->doAction(LSR2interrupted, msg);
				timerBz = new TimerBZ(disp,3,LSR2notInterrupted, RUTSCHE_2_LEER);
				//TODO setze contextData Rampe2 voll auf false;
				break;

				case LSR1interrupted : 
				//cout << "LSR1interrupted" << endl;
				timerBz = new TimerBZ(disp,3,LSR1notInterrupted,RUTSCHE_1_VOLL);
				fisrsState->doAction(LSR1interrupted, msg);
				//TODO setze contextData Rampe1 voll auf true;
				break;



				case LSR2interrupted : 
				timerBz = new TimerBZ(disp,3,LSR2notInterrupted, RUTSCHE_2_VOLL);
				fisrsState->doAction(LSR2interrupted, msg);
				//TODO setze contextData Rampe2 voll auf true;
				break;

				case RUTSCHE_1_VOLL:
				contextData->setRampe1Voll(true);


				cout << "Rutsche 1" << contextData->getRampe1Voll() <<"und Rutsche 2: " <<contextData->getRampe2Voll() << endl;
				fisrsState->doAction(RUTSCHE_1_VOLL, msg);
				break;

				case RUTSCHE_2_VOLL:
				//cout << "Rutsche 1: " << contextData->getRampe1Voll() <<"und Rutsche 2: " <<contextData->getRampe2Voll() << endl;
				fisrsState->doAction(RUTSCHE_2_VOLL, msg);
				break;

				case RUTSCHE_1_LEER:
					contextData->setRampe1Voll(false);
					//cout << "Rutsche leer auf 1--- Nach timer" << endl;
					fisrsState->doAction(RUTSCHE_1_LEER, msg);

					break;

				case RUTSCHE_2_LEER:
					contextData->setRampe2Voll(false);
					//cout << "Rutsche leer auf 2---  Nach timer" << endl;
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
					cout << "---------Time Over" << endl;
					break;

				case FA2_RUNNING:
					contextData->setF2Running(true);


//
//				case FA2_STOPPED:
//					if(FESTO_TYPE == 1) {
//						if(contextData->getWKCount() >0) {
//							actions->startFB();
//						}



					break;

				case FA2_STOPPED:
					contextData->setF2Running(false);
					if(contextData->getWKCount() >0 ) {

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


