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
	actions->startFB();

}
    void BZEinlauf::exit() {

    }
    void BZEinlauf::estp() {


    }
    void BZEinlauf::doAction(int event, _pulse msg){

    		switch (msg.code) {


    		// checke ob höhenmesser interrupt angekommen ist dann next state
    		case 12 :	new(this) BZHoehenmessung;
    					entry();
    					break;

    		}

    	}
