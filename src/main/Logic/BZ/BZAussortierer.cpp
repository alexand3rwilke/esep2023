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
			// checke ob das WK das gesuchte ist, sonst aussortieren und wieder in BZready
			if(contextData->getErkanntesWk() == contextData->getZielWk()) {
			actions->durchlassen();
			// TODO : Vielleicht noch eine Sekunde weiterlaufen lassen damit es in die Rutsche geht
			// TODO : Vielleicht brauchen wir noch einen Ruschen state um zu warten bis das WK die rutsche runtergerutscht ist, damit wir keine feste Zeit warten müssen
			} else {
			exit();
			new(this)BZready;
			}
    		break;



    		case LSE2interrupted :
    		    exit();
    		    new (this) BZAuslauf;
    		    entry();
    		    break;


			case MTD1interrupted :
			if(contextData->getErkanntesWk() == WK_Bohrung_Normal) {
				contextData->setErkanntesWk(WK_Bohrung_Metal);
			}
			break;
    		    

			// Klassefizierung

			case WK_FLACH :
			contextData->setErkanntesWk(WK_FLACH);
			break;

			case WK_Normal:
			contextData->setErkanntesWk(WK_Normal);
			break;

			case WK_Bohrung_Normal :
			contextData->setErkanntesWk(WK_Bohrung_Normal);
			break;

			case WK_UNDEFINED :
			contextData->setErkanntesWk(WK_UNDEFINED);
			break;

    		}

	}
