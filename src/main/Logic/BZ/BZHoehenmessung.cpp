/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZHoehenmessung.h"
#include "BZAussortierer.h"



void BZHoehenmessung::entry() {

	cout << "\n  BZHoehenmessung entry\n" << endl;
	actions->moveSlower();

	contextData->registerForAdc(stateId);

}
    void BZHoehenmessung::exit() {
    	actions->moveFaster();
    }
    void BZHoehenmessung::estp() {


    }
    void BZHoehenmessung::doAction(int event, _pulse msg){

//    	int adcHeight = msg.value.sival_int
//    	if( contextData->getWerkstueckType() != getWKType(adcHeight) 9 {
//    		new (this) BZAussortieren;
//    	} else {
//
//    		new (this) BZDurchlassen
//    	}





		switch (event) {



		case ADC_WK_NIN_HM :
			exit();
			new(this) BZAussortierer;
			entry();
			break;

		}


    }
