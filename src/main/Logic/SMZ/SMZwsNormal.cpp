/*
 * SMZwsNormal.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "SMZwsNormal.h"


void SMZwsNormal::entry(){
	cout << "[SMZ] - Bitte WS mit Normal drauflegen" << endl;
	actions->yellowOn();
}

void SMZwsNormal::exit(){


}

void SMZwsNormal::doAction(int event,_pulse msg){

	switch(event){
	case LSA1interrupted:
		cout << "[SMZ] -  Messe WS mit Normal..." << endl;
		actions->startFB();
		actions->startSMZ_hoehe(2);
		actions->yellowLightBlinking();
		break;
	case LSR1interrupted:
		cout << "[SMZ] -  Messung WS mit Normal fertig " << endl;
		actions->stopFB();
		actions->yellowOn();
		break;
	case STRinterrupted:
		exit();
		new(this) SMZwsBohrung;
		entry();
		break;
	}
}
