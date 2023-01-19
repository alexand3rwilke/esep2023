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
		if (FESTO_TYPE == 1){
		actions->startFB();
		cout << "[SMZ] -  Messe WS mit Metall..." << endl;
		actions->startSMZ_hoehe(4);
		actions->yellowLightBlinking();
		}
		break;


	case LSR1interrupted:
		if (FESTO_TYPE == 1){
		cout << "[SMZ] -  Messung fertig " << endl;
		actions->stopFB();
		}
		break;


	case LSA2interrupted:
		if (FESTO_TYPE == 2){
		actions->startFB();
		cout << "[SMZ] -  Messe WS mit Metall..." << endl;
		actions->startSMZ_hoehe(4);
		actions->yellowLightBlinking();
		}
		break;

	case LSR2interrupted:
		if (FESTO_TYPE == 2){
		cout << "[SMZ] -  Messung fertig " << endl;
		actions->stopFB();
		}
		break;
	case STRinterrupted:
		exit();
		new(this) SMZMesseGrundhoehe;
		entry();
		break;
	}
}
