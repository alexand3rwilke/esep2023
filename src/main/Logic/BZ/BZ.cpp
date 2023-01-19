/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"
#include "../RZ/RZ.h"
#include "../ESZ/ESZ.h"



void BZ::entry(){
	// grünes licht an entry
	actions->greenOn();
	//printf("in BZ");
	//actions->greenOn();

//	substate->contextData

	//substateList.push_back(substate);

}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff();
	actions->stopFB();
}


void BZ::doAction (int event, _pulse msg) {

	///
				// gebe event an substate weiter


	if(event == LSA1interrupted && FESTO_TYPE ==1) {
		Basestate *newsubState;
		newsubState = new BZEinlauf();
		newsubState->setActions(actions);
		newsubState->setContextData(contextData);
		newsubState->entry();
		newsubState->setStateId(stateId);
		substateList.push_back(newsubState);
		contextData->addWK();
		//cout << contextData->getWKCount() << "ist die aktuelle WK anzahl" << endl;

	}

	if(event == LSA2interrupted && FESTO_TYPE ==2) {
			Basestate *newsubState;
			newsubState = new BZEinlauf();
			newsubState->setActions(actions);
			newsubState->setContextData(contextData);
			newsubState->entry();
			newsubState->setStateId(stateId);
			substateList.push_back(newsubState);
			contextData->addWK();

			if(contextData->getWKCount() == 1 ) {
				MsgSendPulse(contextData->disp->getConnectionID(), -1, FA2_RUNNING, 0);
				cout << "sending message : FA_RUNNING" << endl;

						}
			//cout << contextData->getWKCount() << "ist die aktuelle WK anzahl" << endl;

		}

	switch (event) {

				   case ESTP1interrupted:
					   exit();
					   substateList = {};
					   new (this) ESZ;
					   entry();
					   doAction(event, msg);
					   break;


				   case ESTP2interrupted:
					   exit();
					   substateList = {};
					   new (this) ESZ;
					   entry();
					   doAction(event, msg);
					   break;


				   case STPinterrupted:
					   exit();
				  		new (this) RZ;
				  		entry();
				  		break;

					case STRinterrupted:
						exit();
						new(this) BZ;
						entry();
						break;

					case FEHLER_1:
						exit();
						new(this) FZ;
						entry();
						break;

					case FEHLER_2:
						exit();
						new(this) FZ;
						entry();
						break;
					case RUTSCHE_1_VOLL:
						contextData->setRampe1Voll(true);
						if(FESTO_TYPE == 1) {
							actions->greenOff();
							actions->yellowLightBlinking();
						}

						break;
					case RUTSCHE_2_VOLL:
						contextData->setRampe2Voll(true);
						if(FESTO_TYPE == 2) {
							actions->greenOff();
							actions->yellowLightBlinking();
						}
						break;
					case RUTSCHE_1_LEER:
					contextData->setRampe1Voll(false);
					if(FESTO_TYPE == 1) {
						actions->yellowOff();
						actions->greenOn();

					}
					break;

					case RUTSCHE_2_LEER:
					contextData->setRampe2Voll(false);
					if(FESTO_TYPE == 2) {
						actions->yellowOff();
						actions->greenOn();

					}
					break;
					}


	for(Basestate *stateFromList :substateList ) {


	stateFromList->doAction(event, msg);
	//cout << "folgendes event wird an den substate weitergegebern: " << event << endl;

	//

	}
}

