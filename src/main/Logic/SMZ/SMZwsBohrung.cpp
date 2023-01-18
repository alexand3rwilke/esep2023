/*
 * SMZwsBohrung.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "SMZwsBohrung.h"




void SMZwsBohrung::entry(){
	cout << "[SMZ] - Bitte WS mit Bohrung drauflegen" << endl;

	actions->yellowOn();
}

void SMZwsBohrung::exit(){


}

void SMZwsBohrung::doAction(int event,_pulse msg){

	switch(event){
	case LSA1interrupted:
		cout << "[SMZ] -  Messe WS mit Bohrung..." << endl;
		actions->startFB();
		actions->startSMZ_hoehe(3);
		actions->yellowLightBlinking();
		break;
	case LSR1interrupted:
		cout << "[SMZ] -  Messung WS mit Bohrung fertig " << endl;
		actions->stopFB();
		actions->yellowOn();
		break;
	case STRinterrupted:
		exit();
		new(this) SMZwsMetall;
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

