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
	if(FESTO_TYPE == 1) {

		actions->moveSlower();
	}

	stateTimer = new SimpleTimer(this->contextData->disp);
	stateTimer->startTimer();


	//contextData->registerForAdc(stateId);

}
    void BZHoehenmessung::exit() {

    	if(FESTO_TYPE == 1) {

        	actions->moveFaster();
    		}


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

			cout << stateTimer->getTime() << " ist die abgelaufene ZEIT ####" << endl;
			if(stateTimer->getTime() > 0.5) {
			exit();
			new(this) BZAussortierer;
			entry();

			}

			break;

		}


    }
