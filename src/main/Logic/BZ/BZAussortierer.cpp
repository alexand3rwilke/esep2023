/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZAuslauf.h"
#include "BZAussortierer.h"
#include "BZUebergabe.h"
#include "BZ.h"



void BZAussortierer::entry() {


	cout << "\n  BZAussortierer entry\n" << endl;

	if(FESTO_TYPE == 1){
		stateTimer->startTimer();
	}

	if(FESTO_TYPE == 2) {
		// << "Das Werkstueck soll aussortiert werden:  " << contextData->getAussortierenForWerkstueckInStateID(stateId) <<"  an state ID: " << stateId<<endl;
	}
}

    void BZAussortierer::exit() {
    	if(FESTO_TYPE == 1){
    		stateTimer->stopTimer();
        	stateTimer->resetTimer();
    	}
		cout << "[Sortierer] Gesuchtes WS:"<< contextData->werkstuckReihenfolgeList.at(contextData->getwkReihenfolgeIndex() % contextData->werkstuckReihenfolgeList.size()) << endl;
		cout << "[Sortierer] Gescanntes WS:"<< contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp << endl;

    }
    void BZAussortierer::estp() {


    }

void BZAussortierer::doAction(int event, _pulse msg){

	switch (event) {
		case LSE1interrupted :
			if(stateTimer->getTime() > 1.5) {
				exit();
				new(this) BZUebergabe;
				entry();
			}
			break;

		case LSE2interrupted :
			exit();
			new(this) BZAuslauf;
			entry();
			break;



		case LSSinterrupted :

				// Hier wird der aktuelle WkType des States mit dem gesuchten WK verglichen
				// Wenn es das gesuchte ist, wird die schranke geöffnet und das gesuchte einen hochgezählt (zeiger auf das nächste WK der Reihenfolgeliste)
				// Wenn es das Falsche ist, geht es in die aussortieren() methode, welche die Rutschen checket und je nach kapazität auf der jeweiligen Rutsche aussortiert.
			if(contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp ==
				contextData->werkstuckReihenfolgeList.at(contextData->getwkReihenfolgeIndex()
				% contextData->werkstuckReihenfolgeList.size())) {

				actions->durchlassen();
				contextData->setAussortierenForWerkstueckInStateID(stateId, false);
				contextData->increaseWkReihenfolgeIndex();

			} else {
				
				aussortieren();

			}
			break;



			case MTD1interrupted :
			if(contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp == WK_Bohrung) {
				contextData->setGescanntWKMapForStateForIndex(stateId,WK_Bohrung_Metal,contextData->getGescanntWKMapForStateForIndex(stateId).mittlereHoehe);
				cout << "[Sortierer] WS enthält Metall! \n" << endl;

			}
			break;

//			case LSS1notInterrupted:
//				actions->aussortieren();
//				exit();
//				new(this)BZrutsche;
//				entry();
//				break;
//
	}
}


void BZAussortierer::aussortieren() {


//    	if (FESTO_TYPE == 2 && contextData->getRampe2Voll()) {
//			MsgSendPulse(contextData->disp->getConnectionID(), -1, FEHLER_2,0);                      /// Unten bei Festo 2 -------------
//			//actions->stopFB();
//		}else if(contextData->getRampe1Voll() && contextData->getRampe2Voll()) {
//
//    		if(FESTO_TYPE == 1){
//				MsgSendPulse(contextData->disp->getConnectionID(), -1, FEHLER_1,0);    	// Von welcher Festo der Fehler kam kann im State Aussortierer abgespeichert werden
//			}else {
//				MsgSendPulse(contextData->disp->getConnectionID(), -1, FEHLER_2,0);
//			}
//        }else if(!contextData->getRampe1Voll() && contextData->getRampe2Voll()) {
//    		actions->aussortieren();
//    		exit();				// Brauchen wir vlt nicht
//            new (this) BZrutsche;
//            entry();
//	   }else if(contextData->getRampe1Voll() && !contextData->getRampe2Voll()) {
//					actions->durchlassen();
//	   } else if(contextData->getRampe1Voll() && contextData->getRampe2Voll()){
//		actions->stopFB();
//	   } else {
//
//	   }

	contextData->setAussortierenForWerkstueckInStateID(stateId,true);

	if(FESTO_TYPE == 1){

		if(contextData->getRampe1Voll() && contextData->getRampe2Voll()) {
			MsgSendPulse(contextData->disp->getConnectionID(), -1, FEHLER_1,0);

		}

		else if(!contextData->getRampe1Voll() && contextData->getRampe2Voll()) {
			actions->aussortieren();
			exit();				// Brauchen wir vlt nicht
			new (this) BZrutsche;
			entry();

		}

		else if(contextData->getRampe1Voll() && !contextData->getRampe2Voll()) {
			actions->durchlassen();
		}
		else if(!contextData->getRampe1Voll() && !contextData->getRampe2Voll()) {
			if(contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp == WK_FLACH && FESTO_TYPE == 1) {
					actions->aussortieren();
					exit();
					new (this) BZrutsche;
					entry();
				} else
					actions->durchlassen();
				}

		}
	// FESTO1 ENDE

	if(FESTO_TYPE == 2 ){

		if(contextData->getRampe2Voll()) {
			MsgSendPulse(contextData->disp->getConnectionID(), -1, FEHLER_2,0);
		}

		else if(!contextData->getRampe2Voll()) {
			actions->aussortieren();
			exit();
			new (this) BZrutsche;
			entry();

		}
	}
}




