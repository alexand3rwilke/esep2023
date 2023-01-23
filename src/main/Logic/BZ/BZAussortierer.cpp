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


	stateTimer->startTimer();


	if(FESTO_TYPE == 2) {
		cout << "Das Werkstueck soll aussortiert werden:  " << contextData->getAussortierenForWerkstueckInStateID(stateId) <<"  an state ID: " << stateId<<endl;

	}



}

    void BZAussortierer::exit() {

     	stateTimer->stopTimer();
        	stateTimer->resetTimer();

		cout << "------------Gesucht:"<< contextData->werkstuckReihenfolgeList.at(contextData->getwkReihenfolgeIndex() % contextData->werkstuckReihenfolgeList.size()) << endl;
		cout << "------------Folgendes WK wurde gescannt:"<< contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp << endl;

    }
    void BZAussortierer::estp() {


    }


    void BZAussortierer::doAction(int event, _pulse msg){
//
//    		// wenn fertig dann in Auslauf


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



    		case LSS1interrupted :



    				// Hier wird der aktuelle WkType des States mit dem gesuchten WK verglichen
    				// Wenn es das gesuchte ist, wird die schranke geöffnet und das gesuchte einen hochgezählt (zeiger auf das nächste WK der Reihenfolgeliste)
    				// Wenn es das Falsche ist, geht es in die aussortieren() methode, welche die Rutschen checket und je nach kapazität auf der jeweiligen Rutsche aussortiert.
				if(contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp ==
					contextData->werkstuckReihenfolgeList.at(contextData->getwkReihenfolgeIndex()
					% contextData->werkstuckReihenfolgeList.size())) {

			actions->durchlassen();
			contextData->setAussortierenForWerkstueckInStateID(stateId, false);
			contextData->increaseWkReihenfolgeIndex();

			// TODO : Vielleicht noch eine Sekunde weiterlaufen lassen damit es in die Rutsche geht
			// TODO : Vielleicht brauchen wir noch einen Ruschen state um zu warten bis das WK die rutsche runtergerutscht ist, damit wir keine feste Zeit warten müssen
			} else {
				//TODO ENTFERNEN

//    							actions->durchlassen();
//    							contextData->setAussortierenForWerkstueckInStateID(stateId, false);
//    							contextData->increaseWkReihenfolgeIndex();

    		aussortieren();


    			}



    		    break;


			case MTD1interrupted :
			if(contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp == WK_Bohrung) {
				contextData->setGescanntWKMapForStateForIndex(stateId,WK_Bohrung_Metal,contextData->getGescanntWKMapForStateForIndex(stateId).mittlereHoehe);

			cout << "Werkstück enthält Metall \n" << endl;

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




