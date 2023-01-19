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
		actions->startFB();
		cout << "[SMZ] -  Messe Werkstück mit Bohrung..." << endl;
		actions->startSMZ_hoehe(3);
		actions->yellowLightBlinking();
		break;
	case LSA2interrupted:
		actions->startFB();
		cout << "[SMZ] -  Messe Werkstück mit Bohrung..." << endl;
		actions->startSMZ_hoehe(3);
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
		new(this) SMZwsMetall;
		entry();
		break;

	}

}

