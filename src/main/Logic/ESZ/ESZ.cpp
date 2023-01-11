/*
 * ESZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "ESZ.h"


void ESZ::entry(){
	//Was bereits in Aktorik direkt gemacht wird
	//AMP Rot
	//FB Stopp
	resetCounter = 0;
	actions->ampAllOff();
	actions->stopFB();
	actions->redLightBlinkingFast();
	actions->yellowLightBlinking();
	schalteRaus = false;
	// substate GUFZ

}

void ESZ::exit(){
	actions->moveFaster();

}

void ESZ::doAction(int event, _pulse msg){

	switch(event){
	case ESTPnotInterrupted:schalteRaus = true;
	break;
	case ESTPinterrupted: entry();
	break;
	case RSTinterrupted:
		if(resetCounter == 0){
			actions->redOff();
			actions->yellowOn();
			resetCounter++;
		} else if(resetCounter == 1 && schalteRaus){

			actions->yellowOff();
			resetCounter++;
			//Todo check wenn keine fehler
			exit();
			new (this) RZ;
		}
	break;
	}



}

