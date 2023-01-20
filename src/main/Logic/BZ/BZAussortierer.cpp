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



    		case LSS1interrupted :


    			if (FESTO_TYPE == 1) {
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

    			}

    			if (FESTO_TYPE == 2) {


    				if(contextData->getAussortierenForWerkstueckInStateID(stateId)) {

    					// HIER RUTSCHE CHEKEN
					exit();
					new(this)BZrutsche;
					entry();
					} else {
					actions->durchlassen();
					}
    			}

    		    break;


			case MTD1interrupted :
			if(contextData->getGescanntWKMapForStateForIndex(stateId).werkstueckTyp == WK_Bohrung_Normal) {
				contextData->setGescanntWKMapForStateForIndex(stateId,WK_Bohrung_Metal,contextData->getGescanntWKMapForStateForIndex(stateId).mittlereHoehe);

			cout << "Werkstück enthält Metall \n" << endl;

			}
			break;
    		    


    		}

	}

    void BZAussortierer::aussortieren() {
    	contextData->setAussortierenForWerkstueckInStateID(stateId,true);

    	if(contextData->getRampe1Voll() && contextData->getRampe2Voll()) {
    		// FEHLERZUSTAND, sollte hier nicht reinkommen


    	}

    	if(!contextData->getRampe1Voll() && !contextData->getRampe2Voll()) {
        		actions->durchlassen();
        	}

    	if(!contextData->getRampe1Voll() && contextData->getRampe2Voll()) {
            		exit();
            		new (this) BZrutsche;
            		entry();
            	}

    	if(contextData->getRampe1Voll() && !contextData->getRampe2Voll()) {
                		actions->durchlassen();
                	}
    }
