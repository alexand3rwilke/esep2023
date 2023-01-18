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

	//TODO MUSS NOCH ANGEPAST WERDEN
	cout << "\n  BZAussortierer entry\n" << endl;
	cout << "\n  Das Gesuchte WK ist: " << contextData->getGesuchtWKMapForStateForIndex(stateId) <<  "\n" << endl;



}
    void BZAussortierer::exit() {

    }
    void BZAussortierer::estp() {


    }
    void BZAussortierer::doAction(int event, _pulse msg){
//
//    		// wenn fertig dann in Auslauf


    	switch (event) {
    		case LSE1interrupted :
    			exit();
    			new(this) BZUebergabe;
    			entry();
    			break;



    		case LSS1interrupted :
			// checke ob das WK das gesuchte ist, sonst aussortieren und wieder in BZready+


    			contextData->getLatestRegisterForAdcState();
    			cout << "------------Aussortierer Test:"<< endl;
				cout << "------------Gesucht:"<< contextData->getGesuchtWKMapForStateForIndex(stateId) << endl;

				//cout << "------------Folgendes WK wurde gescannt:"<< contextData->getGescanntWKMapForStateForIndex(stateId) << endl;


			if(contextData->getGescanntWKMapForStateForIndex(stateId) == contextData->getGesuchtWKMapForStateForIndex(stateId)) {
			actions->durchlassen();
			// TODO : Vielleicht noch eine Sekunde weiterlaufen lassen damit es in die Rutsche geht
			// TODO : Vielleicht brauchen wir noch einen Ruschen state um zu warten bis das WK die rutsche runtergerutscht ist, damit wir keine feste Zeit warten müssen
			} else {

			exit();
			new(this)BZrutsche;
			entry();


			}
    		break;



    		case LSE2interrupted :
    		    exit();
    		    new (this) BZAuslauf;
    		    entry();
    		    break;


			case MTD1interrupted :
			if(contextData->getGescanntWKMapForStateForIndex(stateId)->werkstueckTyp == WKB) {
				Werkstueck *ws1 = contextData->getGescanntWKMapForStateForIndex(stateId);
				contextData->setGescanntWKMapForStateForIndex(stateId,*ws1->setWkType(WKBM));

				cout << "Werkstück enthält Metall \n" << endl;

			}
			break;
    		    

			// Klassefizierung

			case WK_FLACH :
			Werkstueck *ws2 = contextData->getGescanntWKMapForStateForIndex(stateId);
			contextData->setGescanntWKMapForStateForIndex(stateId,ws2->setWkType(WKF));
			cout << "WERKSTÜCK AUF FLACH GESETZT \n" << endl;
			break;

			case WK_Normal:
			Werkstueck *ws3 = contextData->getGescanntWKMapForStateForIndex(stateId);
			contextData->setGescanntWKMapForStateForIndex(stateId,ws3->setWkType(WKN));
			cout << "WERKSTÜCK AUF NORMAL GESETZT \n" << endl;
			break;

			case WK_Bohrung_Normal :
			Werkstueck *ws4 = contextData->getGescanntWKMapForStateForIndex(stateId);
			contextData->setGescanntWKMapForStateForIndex(stateId,ws4->setWkType(WKB));
			cout << "WERKSTÜCK AUF BOHRUNG NORMAL GESETZT \n" << endl;
			break;

			case WK_UNDEFINED :
			Werkstueck *ws5 = contextData->getGescanntWKMapForStateForIndex(stateId);
			contextData->setGescanntWKMapForStateForIndex(stateId,ws5->setWkType(WKU));
			cout << "WERKSTÜCK AUF UNDEFINED GESETZT \n" << endl;
			break;

    		}

	}
