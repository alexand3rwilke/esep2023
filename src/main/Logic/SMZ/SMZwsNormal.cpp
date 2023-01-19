/*
 * SMZwsNormal.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "SMZwsNormal.h"


void SMZwsNormal::entry(){
	cout << "[SMZ] - Bitte normales Werkstück drauflegen" << endl;
	actions->yellowOn();
}

void SMZwsNormal::exit(){


}

void SMZwsNormal::doAction(int event,_pulse msg){

	switch(event){
	case LSA1interrupted:
		actions->startFB();
		cout << "[SMZ] -  Messe normales Werkstück..." << endl;
		actions->startSMZ_hoehe(2);
		actions->yellowLightBlinking();
		break;
	case LSA2interrupted:
		actions->startFB();
		cout << "[SMZ] -  Messe normales Werkstück..." << endl;
		actions->startSMZ_hoehe(2);
		actions->yellowLightBlinking();
		break;
	case LSR1interrupted:
		cout << "[SMZ] -  Messung fertig " << endl;
		actions->stopFB();
		break;
	case LSR2interrupted:
		cout << "[SMZ] -  Messung fertig " << endl;
		actions->stopFB();
		break;
	case STRinterrupted:
		exit();
		new(this) SMZwsBohrung;
		entry();
		break;
	}
}
