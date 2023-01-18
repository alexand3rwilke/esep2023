/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZready.h"
#include "BZEinlauf.h"


void BZready::entry() {

	//actions->stopFB();
	cout << "\n  BZready entry\n" << endl;
}
    void BZready::exit() {

    }
    void BZready::estp() {


    }
    void BZready::doAction(int event, _pulse msg){


    	switch(event){
    		// check ob LSE interrupt bekommt
    		case LSA1interrupted :
    			contextData->setGescanntWKMapForStateForIndex(stateID, new Werkstueck);
    			exit();
    			new(this) BZEinlauf;
    			entry();
    			break;

    		case LSA2interrupted :

				exit();
				new(this) BZEinlauf;
				entry();
				break;

    		case LSE1interrupted :

				exit();
				new(this) BZEinlauf;
				entry();
				break;

    		case WSDATA:
    			//Reihenfolge von Übergabe : mittlereHöhe->WKType->ID(Key von map)
    			if(FESTO_TYPE == 2){
    				Werkstueck *ws2 = new Werkstueck();
    				if(contextData->gescanntesWKMap.size()== 0){
        				ws2->setMittlereHoehe(msg.value.sival_int);
    				}else{
    				ws2->setWkType(msg.value.sival_int);
    				contextData->setGescanntWKMapForStateForIndex(msg.value.sival_int, ws2);
    				}
    			}
    			break;


    		// case LSE2interrupted :

			// 	exit();
			// 	new(this) BZEinlauf;
			// 	entry();
			// 	break;

    	}




    	}
