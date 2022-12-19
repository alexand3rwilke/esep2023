/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZHoehenmessung.h"
#include "BZAussortierer.h"



void BZHoehenmessung::entry() {
	actions->moveSlower();

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



    }
