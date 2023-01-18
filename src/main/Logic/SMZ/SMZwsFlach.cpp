/*
 * WarteAufFlachesWS.cpp
 *
 *  Created on: 16.01.2023
 *      Author: Jobut
 */

#include "SMZwsFlach.h"

void SMZwsFlach::entry(){
	cout << "[SMZ] - Bitte flaches WS drauflegen" << endl;
	actions->yellowOn();

}

void SMZwsFlach::exit(){


}

void SMZwsFlach::doAction(int event,_pulse msg){

	switch(event){
	case LSA1interrupted:
		cout << "[SMZ] -  Messe flaches Werkstück ..." << endl;
		actions->startFB();
		actions->startSMZ_hoehe(1);
		actions->yellowLightBlinking();
		break;
	case LSR1interrupted:
		cout << "[SMZ] -  Messe Flaches fertig ..." << endl;
		actions->stopFB();
		actions->yellowOn();
		break;
	case STRinterrupted:
		exit();
		new(this) SMZwsNormal;
		entry();
		break;

	case ADC_WK_IN_HM :
		actions->moveSlower();
		break;

	case ADC_WK_NIN_HM :
		actions->moveFaster();
		break;

	}

}

