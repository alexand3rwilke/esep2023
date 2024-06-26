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
#include "../../Imports.h"
#include "../../hal/SensorWrapper/SensorWrapper.h"



void BZ::entry(){
	// grünes licht an entry
	actions->greenOn();
//	if(0<contextData->getWKCount()){   // ---------------------------- Das würde nur gehen wenn FB2 leer ist
//		//weiter
//		actions->startFB();
//	}
	//printf("in BZ");

	if(SensorWrapper::readPin(gpio_bank_0, 27)  == 0){
			if(FESTO_TYPE == 1) {
				MsgSendPulse(contextData->disp->getConnectionID(), -1, ESTP1interrupted, 0);


			} else {
				MsgSendPulse(contextData->disp->getConnectionID(), -1, ESTP2interrupted, 0);

			}

			}

		if(SensorWrapper::readPin(gpio_bank_0, 15)  == 0){
				if(FESTO_TYPE == 1) {
					MsgSendPulse(contextData->disp->getConnectionID(), -1, RUTSCHE_1_VOLL, 0);

				} else {
					MsgSendPulse(contextData->disp->getConnectionID(), -1, RUTSCHE_2_VOLL, 0);
				}

				}
}

void BZ::exit(){
	actions->greenOff();
	actions->stopFB();
}


void BZ::doAction (int event, _pulse msg) {

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
		//cout << contextData->getWKCount() << "ist die aktuelle WK anzahl" << endl;
	}

	if(event == LSA2interrupted && FESTO_TYPE ==2) {

		Basestate *newsubState;
		newsubState = new BZEinlauf(); // BZready
		newsubState->setActions(actions);
		newsubState->setContextData(contextData);
		newsubState->entry();
		newsubState->setStateId(stateId);
		contextData->setGescanntWKMapForStateForIndex(newsubState->getStateId(),0,0);


		substateList.push_back(newsubState);
		contextData->addWK();
		//stateId++;
		cout << "StateCounter is now: " << stateId << endl;   // ---------- Muss raus

		if(contextData->getWKCount() == 1 ) {
		MsgSendPulse(contextData->disp->getConnectionID(), -1, FA2_RUNNING, 0);
		//cout << "sending message : FA_RUNNING" << endl;

		}
	//cout << contextData->getWKCount() << "ist die aktuelle WK anzahl" << endl;

	}

	switch (event) {

	   case ESTP1interrupted:
		   exit();
		   resetBZ();
		   new (this) ESZ;
		   entry();
		   doAction(event, msg);
		   break;


	   case ESTP2interrupted:
		   exit();
		   resetBZ();
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
						auto it = substateList.begin();
						std::advance(it, i);
						substateList.erase(it);
						break;

					}
				}
				break;
			case WK_FLACH :
				if(FESTO_TYPE == 2) {
					contextData->setGescanntWKAbsoluteHoeheForStateForIndex(0,msg.value.sival_int);
					contextData->setFlippedForWerkstueckInStateID(0, contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp!= WK_FLACH);
				} else {
					setWkInStateWhereNotSet(WK_FLACH,msg.value.sival_int);
				}
			break;

			case WK_Normal :
				if(FESTO_TYPE == 2) {
					contextData->setGescanntWKAbsoluteHoeheForStateForIndex(0,msg.value.sival_int);
					contextData->setFlippedForWerkstueckInStateID(0, contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp != WK_Normal);
				} else {
					setWkInStateWhereNotSet(WK_Normal,msg.value.sival_int);
				}
			break;

			case WK_Bohrung_Metal :
				if(FESTO_TYPE == 2) {
					contextData->setGescanntWKAbsoluteHoeheForStateForIndex(0,msg.value.sival_int);
				contextData->setFlippedForWerkstueckInStateID(0, contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp != WK_Bohrung_Metal);
				} else {
					setWkInStateWhereNotSet(WK_Bohrung_Metal,msg.value.sival_int);
				}
			break;

			case WK_Bohrung :
				if(FESTO_TYPE == 2) {
					contextData->setGescanntWKAbsoluteHoeheForStateForIndex(0,msg.value.sival_int);
					contextData->setFlippedForWerkstueckInStateID(0, contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp != WK_Bohrung);
				} else {
					setWkInStateWhereNotSet(WK_Bohrung,msg.value.sival_int);
				}
			break;

			case WK_UNDEFINED :
				if(FESTO_TYPE == 2) {
					contextData->setGescanntWKAbsoluteHoeheForStateForIndex(0,msg.value.sival_int);
					contextData->setFlippedForWerkstueckInStateID(0, contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp != WK_UNDEFINED);
				} else {
					setWkInStateWhereNotSet(WK_UNDEFINED,msg.value.sival_int);
				}
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
		// ____
//		case RUTSCHE_2_VOLL:
//			contextData->setRampe2Voll(true);
//			if(FESTO_TYPE == 2) {
//				actions->greenOff();
//				actions->yellowLightBlinking();
//			}
//			break;
//		case RUTSCHE_1_LEER:
//		contextData->setRampe1Voll(false);
//		if(FESTO_TYPE == 1) {
//			actions->yellowOff();
//			actions->greenOn();
//
//		case DELETE_STATE :
//			for(int i = 0; i < substateList.size(); i++ ) {
//				if(substateList.at(i)->getStateId() == msg.value.sival_int) {
//					cout << "DELETING STATE WITH ID: " << substateList.at(i)->getStateId() << endl;
//
//					auto it = substateList.begin();
//					std::advance(it, i);
//					substateList.erase(it);
//					break;
//
//				}
//			}
//			break;
//
//
//
//			// TODO Werkstück erkennung testen
//		case WK_FLACH :
//			if(FESTO_TYPE == 2) {
//			// Unnötig, da ein Flaches WK geflippt = ein Flaches bleibt
//			if(contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp!= WK_FLACH) {
//				cout << "[Context] Werkstueck hat sich geändert! \n" << endl;
//			}
//
//			} else {
//				setWkInStateWhereNotSet(WK_FLACH,msg.value.sival_int);
//			}
//
//
//		break;
//
//		case WK_Normal :
//			if(FESTO_TYPE == 2) {
//
//				switch (contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp) {
//
//					case WK_Bohrung:
//						contextData->setFlippedForWerkstueckInStateID(0, true);
//						contextData->setGescanntWKType(0,WK_Normal);
//						break;
//
//					case WK_Bohrung_Metal:
//						contextData->setFlippedForWerkstueckInStateID(0, true);
//						contextData->setGescanntWKType(0,WK_Normal);
//						break;
//
//					case WK_Normal:
//						break;
//
//					default :
//						cout << "[Context] Werkstueck hat sich geändert! \n" << endl;
//						break;
//				}
//
//			} else {
//				setWkInStateWhereNotSet(WK_Normal,msg.value.sival_int);
//			}
//
//		break;
//
//		case WK_Bohrung_Metal :
//			if(FESTO_TYPE == 2) {
//
//				if(contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp == WK_Normal) {
//
//					contextData->setFlippedForWerkstueckInStateID(0,true);
//					contextData->setGescanntWKType(0,WK_Bohrung_Metal);
//				}
//
//				else if(contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp != WK_Bohrung_Metal){
//
//					cout << "[Context] Werkstueck hat sich geändert! \n" << endl;
//				}
//
//
//			} else {
//				setWkInStateWhereNotSet(WK_Bohrung_Metal,msg.value.sival_int);
//			}
//
//		break;
//
//		case WK_Bohrung :
//			if(FESTO_TYPE == 2) {
//
//				if(contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp == WK_Normal) {
//
//					contextData->setFlippedForWerkstueckInStateID(0,true);
//					contextData->setGescanntWKType(0,WK_Bohrung);
//					}else if(contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp != WK_Bohrung){
//
//						cout << "[Context] Werkstueck hat sich geändert! \n" << endl;
//					}
//
//			} else {
//				setWkInStateWhereNotSet(WK_Bohrung,msg.value.sival_int);
//			}
//
//		break;
//
//		case WK_UNDEFINED :
//			if(FESTO_TYPE == 2) {
//
//			//contextData->setFlippedForWerkstueckInStateID(0, contextData->getGescanntWKMapForStateForIndex(0).werkstueckTyp != WK_UNDEFINED);
//			} else {
//				setWkInStateWhereNotSet(WK_UNDEFINED,msg.value.sival_int);
//			}
//
//		break;
//		}
//		break;
//
//		case RUTSCHE_2_LEER:
//		contextData->setRampe2Voll(false);
//		if(FESTO_TYPE == 2) {
//			actions->yellowOff();
//			actions->greenOn();
//
//		}
//		break;
		//__
	}

	for(Basestate *stateFromList :substateList ) {
		stateFromList->doAction(event, msg);
		//cout << "folgendes event wird an den substate weitergegebern: " << event << endl;
	}
}

void BZ::setWkInStateWhereNotSet(int wkType, int durchschnittHoehe) {
	int index = 0;
	for(int i = 0;i < substateList.size(); i++) {
		index = substateList.at(i)->getStateId();
		if(contextData->getGescanntWKMapForStateForIndex(index).werkstueckTyp == 0) {
			contextData->setGescanntWKMapForStateForIndex(index,wkType, durchschnittHoehe);
		}
	}
}

void BZ::resetBZ(){
	stateId = 0;
	for(Basestate *state : substateList) {
			delete state;
		}
	substateList = {};

	contextData->resetCount();
	contextData->resetContextData();
}

