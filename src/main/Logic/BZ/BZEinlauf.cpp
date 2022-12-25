/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZEinlauf.h"
#include "BZHoehenmessung.h"
#include "../Actions.h"




void BZEinlauf::entry() {
	cout << "\n  BZEinlauf entry\n" << endl;
	actions->startFB();
	contextData->addWK();

}
    void BZEinlauf::exit() {

    }
    void BZEinlauf::estp() {


    }
    void BZEinlauf::doAction(int event, _pulse msg){



    		switch (event) {



    		case ADC_WK_IN_HM :
    			exit();
    			new(this) BZHoehenmessung;
    			entry();
    			break;

    		}

    	}
