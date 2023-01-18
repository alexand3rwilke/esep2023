

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




Context::Context(Dispatcher *dispatcher, Actions *actions, ContextData  *contextData,vector<int> werkstuckReihenfolgeList) {


	//TimerBZ timerBz;
//	TimerBZ timerBz;
//			timerBz = new TimerBZ(3,7);
	wkReihenfolgeIndex = 0;
	stateIndex = 0;
	this->werkstuckReihenfolgeList = werkstuckReihenfolgeList;
	this->contextData = contextData;
	this->disp = dispatcher;
		dispID = disp->getConnectionID();

	// Setze State auf RZ
	Basestate *fisrsState;
	fisrsState = new RZ();



	fisrsState->setContextData(contextData);
	fisrsState->setActions(actions);
	//fisrsState->setZielWK(werkstuckReihenfolgeList.at(wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size()));
	//RZ
	fisrsState->setStateId(stateIndex);
	contextData->setGescanntWKMapForStateForIndex(stateIndex,0);
	contextData->setGesuchtWKMapForStateForIndex(stateIndex++,werkstuckReihenfolgeList.at(wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size()));

	fisrsState->entry();

	cout << "GESUCHTES WK WURDE AUF FOLGENDES GESETZT: "<< contextData->getGesuchtWKMapForStateForIndex(/*fisrsState->getStateId()*/0) << "\n" << endl;

	stateList.push_back(fisrsState);

	fisrsState->exit();
		new (fisrsState) SMZ;
		fisrsState->entry(); //TODO ---------------------------------------------------------------------------------------- Nur für den Test


	ContextThread = new std::thread([this]() {eventHandler();});
}

Context::~Context() {
	//delete states;
	for(Basestate *s : stateList) {
		delete s;
	}

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
		events = 	{LSA1interrupted,LSA2interrupted,
					LSE1interrupted,LSE2interrupted,LSE1notInterrupted,
					LSS1interrupted,LSS1notInterrupted,
					LSR1notInterrupted,LSR2notInterrupted,LSR1interrupted,LSR2interrupted,
					STRinterrupted,STRnotInterrupted,STPinterrupted,
					ADC_WK_IN_HM,ADC_WK_NIN_HM,ADC_SINGLE_SAMLING_FINISHED,ADC_START_SINGLE_SAMPLE,
					STR_SMZ,MTD1interrupted,
					ESTP1interrupted,ESTP1notInterrupted, 
					ESTP2interrupted,ESTP2notInterrupted,
					RSTinterrupted,
					WK_FLACH,WK_Normal,WK_Bohrung_Metal,WK_Bohrung_Normal,WK_UNDEFINED,
					WK_REMOVED,WK_ADDED,
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
				   for(int i = 0; i< stateList.size(); i++) {


			   switch(msg.code) {
			   //----------------------------------------------------
			   // EStop
			   case ESTP1interrupted:
				   stateList.at(i)->doAction(ESTP1interrupted, msg);
			 		break;

			   case ESTP1notInterrupted:
			   		stateList.at(i)->doAction(ESTP1notInterrupted, msg);
			   		break;


			   case ESTP2interrupted:
					stateList.at(i)->doAction(ESTP2interrupted, msg);
					break;

			   case ESTP2notInterrupted:
					stateList.at(i)->doAction(ESTP2notInterrupted, msg);
					break;



			   case RSTinterrupted:
			  		stateList.at(i)->doAction(RSTinterrupted, msg);
			  		break;


			   	//----------------------------------------------------

			   case LSA1interrupted:
					   // ADD NEW STATE
					   // TODO hier noch unterscheiden ob wir im firstState sind, um nich am Anfang schon mit 2 states zu starten
					   // Da-> init mit [firstState] in RZ(), dann kommt LSA1 interrupted welches nicht einen neuen State in den vector packen soll...
					  if(!firstState) {
				   	   Basestate *newState = new RZ();
					   newState = new RZ();
					   newState->setContextData(contextData);
					   newState->setActions(actions);
					   newState->entry();
					   newState->doAction(LSA1interrupted, msg);
					   // setze gesuchtes WK auf den aktuellen stand der liste und setze den pointer danach hoch
					   //newState->setZielWK(werkstuckReihenfolgeList.at(wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size()));
					   newState->setStateId(stateIndex);
					   contextData->setGescanntWKMapForStateForIndex(stateIndex,0);
					   contextData->setGesuchtWKMapForStateForIndex(stateIndex++,wkReihenfolgeIndex++ % werkstuckReihenfolgeList.size());
					   stateList.push_back(newState);
					   firstState = false;
					   contextData->addWK();
					   cout << "WK anzahl auf den FB ist : " << contextData->getWKCount();
					  }

				   	// danach normale action
				   stateList.at(i)->doAction(LSA1interrupted, msg);

				   break;

			   case LSE1interrupted:
				   stateList.at(i)->doAction(LSE1interrupted, msg);
				   break;

			   case	LSS1interrupted:
				   stateList.at(i)->doAction(LSS1interrupted , msg);
				   break;

			   case LSE1notInterrupted:
				   stateList.at(i)->doAction(LSE1notInterrupted, msg);
				   break;


			   case ADC_WK_IN_HM:
				   //cout << "ADC_WK_IN_HM \n" << endl;

				   MsgSendPulse(chanID, -1, ADC_START_SINGLE_SAMPLE, 0);
				   stateList.at(i)->doAction(ADC_WK_IN_HM, msg);
				   break;

			   case	ADC_WK_NIN_HM:
				   //cout << "ADC_WK_NIN_HM \n" << endl;

				   stateList.at(i)->doAction(ADC_WK_NIN_HM, msg);
				   break;

			   case ADC_SINGLE_SAMLING_FINISHED:
				   cout << "ADC_SINGLE_SAMLING_FINISHED \n" << endl;
				   stateList.at(i)->doAction(ADC_SINGLE_SAMLING_FINISHED, msg);
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
							stateList.at(i)->doAction(STR_SMZ ,msg);
							break;
						//Taster weniger als 2 Sekunden, dann BZ
						}else{
							stateList.at(i)->doAction(STRinterrupted, msg);
							break;
						}
					}
				   break;

			  case STR_SMZ:
				  stateList.at(i)->doAction(STR_SMZ, msg);
				  break;

			  case STPinterrupted:
				  // if keine Warning
				  stateList.at(i)->doAction(STPinterrupted, msg);
				  break;

			  case MTD1interrupted:
				  stateList.at(i)->doAction(MTD1interrupted, msg);
			   	   break;

			  case LSE2interrupted:
				  stateList.at(i)->doAction(LSE2interrupted,msg);
				  break;
			  case LSA2interrupted:
				  stateList.at(i)->doAction(LSA2interrupted,msg);
				  break;

				case LSR1notInterrupted:
				stateList.at(i)->doAction(LSR1notInterrupted, msg);
				contextData->setRampe1Voll(false);
				//TODO setze contextData Rampe1 voll auf false;
				break;

				case LSR2notInterrupted:
				stateList.at(i)->doAction(LSR2notInterrupted, msg);
				contextData->setRampe2Voll(false);
				//TODO setze contextData Rampe2 voll auf false;
				break;

				case LSR1interrupted : 
				//timerBz;
				//int k =LSR1notInterrupted;
				cout << "LSR1interrupted" << endl;
				timerBz = new TimerBZ(disp,3,LSR1notInterrupted);
				contextData->setRampe1Voll(true);
				stateList.at(i)->doAction(LSR1interrupted, msg);
				//TODO setze contextData Rampe1 voll auf true;
				break;


				case LSR2interrupted:
					cout << "LSR2interrupted" << endl;
				contextData->setRampe2Voll(false);
				stateList.at(i)->doAction(LSR2interrupted, msg);
				//TODO setze contextData Rampe2 voll auf true;
				break;

				// TODO Werkstück erkennung testen
				case WK_FLACH : 
				setWkInStateWhereNotSet(WK_FLACH);
				stateList.at(i)->doAction(WK_FLACH, msg);
				break;

				case WK_Normal :
				setWkInStateWhereNotSet(WK_Normal);
				stateList.at(i)->doAction(WK_Normal, msg);
				break;

				case WK_Bohrung_Metal :
				setWkInStateWhereNotSet(WK_Bohrung_Metal);
				stateList.at(i)->doAction(WK_Bohrung_Metal, msg);
				break;

				case WK_Bohrung_Normal :
				setWkInStateWhereNotSet(WK_Bohrung_Normal);
				stateList.at(i)->doAction(WK_Bohrung_Normal, msg);
				break;

				case WK_UNDEFINED : 
				setWkInStateWhereNotSet(WK_UNDEFINED);
				stateList.at(i)->doAction(WK_UNDEFINED, msg);
				break;

				case WK_ADDED :
				contextData->addWK();
				break;

				case WK_REMOVED :
				contextData->removeWK();
				break;


			   }

			}

		}

}

void Context::setWkInStateWhereNotSet(int wkType) {

	for(int i = 0;i < stateIndex; i++) {
		//cout << "map auf wert 0 ist:" << contextData->getGescanntWKMapForStateForIndex(0) << "\n" << endl;
		//cout << i << "\n" << endl;
//		cout << "--------------------map hat wert: "<< contextData->getGescanntWKMapForStateForIndex(i) << "\n" << endl;
//	cout << "--------------------map hat wert" << "\n" << endl;
	if(contextData->getGescanntWKMapForStateForIndex(i) == 0) {
		contextData->setGescanntWKMapForStateForIndex(0,wkType);
//			cout << "--------------------map hat wert 2" << "\n" << endl;
//				return;
	}
}
//		contextData->getLatestRegisterForAdcState();
//		int adcRecieverStateId = contextData->getLatestRegisterForAdcState();
//		contextData->setGescanntWKMapForStateForIndex(adcRecieverStateId,wkType);


}
