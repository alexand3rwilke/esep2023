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
		contextData->setGescanntWKMapForStateForIndex(newsubState->getStateId(),0,0);
		int gesuchtesWK = contextData->werkstuckReihenfolgeList.at(contextData->getwkReihenfolgeIndex() % contextData->werkstuckReihenfolgeList.size());
		contextData->setGesuchtWKMapForStateForIndex(newsubState->getStateId(),gesuchtesWK);
		contextData->increaseWkReihenfolgeIndex();

		substateList.push_back(newsubState);
		contextData->addWK();
		stateId++;
		cout << "StateCounter is now: " << stateId << endl;
		cout << "New state created with id" << newsubState->getStateId() << endl;



		//cout << contextData->getWKCount() << "ist die aktuelle WK anzahl" << endl;

	}

	if(event == LSA2interrupted && FESTO_TYPE ==2) {

			Basestate *newsubState;
			newsubState->setStateId(stateId);
			newsubState = new BZEinlauf();
			newsubState->setActions(actions);
			newsubState->setContextData(contextData);
			newsubState->entry();
			contextData->setGescanntWKMapForStateForIndex(newsubState->getStateId(),0,0);
			int gesuchtesWK = contextData->werkstuckReihenfolgeList.at(contextData->getwkReihenfolgeIndex() % contextData->werkstuckReihenfolgeList.size());
			contextData->setGesuchtWKMapForStateForIndex(newsubState->getStateId(),gesuchtesWK);
			contextData->increaseWkReihenfolgeIndex();
			newsubState->setStateId(newsubState->getStateId());
			substateList.push_back(newsubState);
			contextData->addWK();
			stateId++;

			if(contextData->getWKCount() == 1 ) {
				MsgSendPulse(contextData->disp->getConnectionID(), -1, FA2_RUNNING, 0);
				cout << "sending message : FA_RUNNING" << endl;

						}
			//cout << contextData->getWKCount() << "ist die aktuelle WK anzahl" << endl;

		}

	switch (event) {

				   case ESTP1interrupted:
					   exit();
					   new (this) ESZ;
					   entry();
					   doAction(event, msg);
					   break;


				   case ESTP2interrupted:
					   exit();
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


					}

	for(Basestate *stateFromList :substateList ) {


	stateFromList->doAction(event, msg);
	//cout << "folgendes event wird an den substate weitergegebern: " << event << endl;

	//

	}
}

