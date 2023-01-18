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
	actions->moveFaster();


}

void SMZwsMetall::doAction(int event,_pulse msg){

	switch(event){
	case LSA1interrupted:
		cout << "[SMZ] -  Messe WS mit Metall..." << endl;
		actions->startFB();
		actions->startSMZ_hoehe(4);
		actions->yellowLightBlinking();
		break;
	case LSR1interrupted:
		cout << "[SMZ] -  Messung WS mit Metall fertig " << endl;
		actions->stopFB();
		actions->yellowOn();
		break;
	case STRinterrupted:
		exit();
		new(this) SMZMesseGrundhoehe;
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
