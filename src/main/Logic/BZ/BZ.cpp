/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"
#include "../RZ/RZ.h"
#include "../ESZ/ESZ.h"
#include <iterator>



void BZ::entry(){
	// grünes licht an entry
	actions->greenOn();
	if(0<contextData->getWKCount()){   // ---------------------------- Das würde nur gehen wenn FB2 leer ist
		//weiter
		actions->startFB();
	}
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

		//contextData->setGesuchtWKMapForStateForIndex(newsubState->getStateId(),gesuchtesWK);

		substateList.push_back(newsubState);
		contextData->addWK();
		stateId++;
		cout << "StateCounter is now: " << stateId << endl;
		cout << "New state created with id" << newsubState->getStateId() << endl;




		//cout << contextData->getWKCount() << "ist die aktuelle WK anzahl" << endl;

	}

	if(event == LSA2interrupted && FESTO_TYPE ==2) {

		Basestate *newsubState;
				newsubState = new BZEinlauf();
				newsubState->setActions(actions);
				newsubState->setContextData(contextData);
				newsubState->entry();
				newsubState->setStateId(stateId);
				contextData->setGescanntWKMapForStateForIndex(newsubState->getStateId(),0,0);


				substateList.push_back(newsubState);
				contextData->addWK();
				stateId++;
				cout << "StateCounter is now: " << stateId << endl;
				cout << "New state created with id" << newsubState->getStateId() << endl;

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

					case DELETE_STATE :
						for(int i = 0; i < substateList.size(); i++ ) {
							if(substateList.at(i)->getStateId() == msg.value.sival_int) {
								cout << "DELETING STATE WITH ID: " << substateList.at(i)->getStateId() << endl;

								auto it = substateList.begin();
								std::advance(it, i);
								substateList.erase(it);
								break;

							}
						}
						break;



						// TODO Werkstück erkennung testen
					case WK_FLACH :
					setWkInStateWhereNotSet(WK_FLACH,msg.value.sival_int);

					break;

					case WK_Normal :
					setWkInStateWhereNotSet(WK_Normal,msg.value.sival_int);

					break;

					case WK_Bohrung_Metal :
					setWkInStateWhereNotSet(WK_Bohrung_Metal,msg.value.sival_int);

					break;

					case WK_Bohrung_Normal :
					setWkInStateWhereNotSet(WK_Bohrung_Normal,msg.value.sival_int);

					break;

					case WK_UNDEFINED :
					setWkInStateWhereNotSet(WK_UNDEFINED,msg.value.sival_int);

					break;
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

void BZ::setWkInStateWhereNotSet(int wkType, int durchschnittHoehe) {
int index = 0;
	for(int i = 0;i < substateList.size(); i++) {
		//cout << "map auf wert 0 ist:" << contextData->getGescanntWKMapForStateForIndex(0) << "\n" << endl;
		//cout << i << "\n" << endl;
//		cout << "--------------------map hat wert: "<< contextData->getGescanntWKMapForStateForIndex(i) << "\n" << endl;
//	cout << "--------------------map hat wert" << "\n" << endl;
		index = substateList.at(i)->getStateId();
	if(contextData->getGescanntWKMapForStateForIndex(index).werkstueckTyp == 0) {
		contextData->setGescanntWKMapForStateForIndex(index,wkType, durchschnittHoehe);
//			cout << "--------------------map hat wert 2" << "\n" << endl;
//				return;
	}
}
//		contextData->getLatestRegisterForAdcState();
//		int adcRecieverStateId = contextData->getLatestRegisterForAdcState();
//		contextData->setGescanntWKMapForStateForIndex(adcRecieverStateId,wkType);


}

