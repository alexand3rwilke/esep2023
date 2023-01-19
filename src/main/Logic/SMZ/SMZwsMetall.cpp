/*
 * SMZwsMetall.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "SMZwsMetall.h"


void SMZwsMetall::entry(){
	cout << "[SMZ] - Bitte WS mit Metall drauflegen" << endl;
	actions->yellowOn();

}

void SMZwsMetall::exit(){


}

void SMZwsMetall::doAction(int event,_pulse msg){

	switch(event){
	case LSA1interrupted:
		actions->startFB();
		cout << "[SMZ] -  Messe WS mit Metall..." << endl;
		actions->startSMZ_hoehe(4);
		actions->yellowLightBlinking();
		break;
	case LSA2interrupted:
		actions->startFB();
		cout << "[SMZ] -  Messe WS mit Metall..." << endl;
		actions->startSMZ_hoehe(4);
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
		new(this) SMZMesseGrundhoehe;
		entry();
		break;
	}
}
