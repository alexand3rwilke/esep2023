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
	actions->redLightBlinking();
	actions->yellowLightBlinking();


	// substate GUFZ

}

void ESZ::exit(){
	actions->moveFaster();

}

void ESZ::doAction(int event, _pulse msg){

	switch(event){

	case ESTP2notInterrupted:schalteRaus = true;
		break;

	case ESTP1notInterrupted:schalteRaus = true;
	break;

	case ESTP1interrupted:
		entry();
		if(FESTO_TYPE == 1) {
			schalteRaus = false;

		}
		break;

	case ESTP2interrupted:
		entry();
		if(FESTO_TYPE == 2) {
			schalteRaus = false;

		}

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

