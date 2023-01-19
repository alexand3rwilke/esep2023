/*
 * WarteAufFlachesWS.cpp
 *
 *  Created on: 16.01.2023
 *      Author: Jobut
 */

#include "SMZwsFlach.h"

void SMZwsFlach::entry(){
	cout << "[SMZ] - Bitte flaches Werkstück drauflegen" << endl;
	actions->yellowOn();

}

void SMZwsFlach::exit(){


}

void SMZwsFlach::doAction(int event,_pulse msg){

	switch(event){

	case LSA1interrupted:
		if (FESTO_TYPE == 1){
		actions->startFB();
		cout << "[SMZ] -  Messe flaches Werkstück ..." << endl;
		actions->startSMZ_hoehe(1);
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
		cout << "[SMZ] -  Messe flaches Werkstück ..." << endl;
		actions->startSMZ_hoehe(1);
		actions->yellowLightBlinking();
		}
		break;

	case LSR2interrupted:
		if (FESTO_TYPE == 2){
		cout << "[SMZ] -  Messung fertig " << endl;
		actions->stopFB();
		}
		break;

//	if(FESTO_TYPE == 1){
//	case LSA1interrupted:
//		actions->startFB();
//		cout << "[SMZ] -  Messe flaches Werkstück ..." << endl;
//		actions->startSMZ_hoehe(1);
//		actions->yellowLightBlinking();
//		break;
//	case LSR1interrupted:
//		cout << "[SMZ] -  Messung fertig." << endl;
//		actions->stopFB();
//		break;
//	} else {
//	case LSA2interrupted:
//		actions->startFB();
//		cout << "[SMZ] -  Messe flaches Werkstück ..." << endl;
//		actions->startSMZ_hoehe(1);
//		actions->yellowLightBlinking();
//		break;
//
//	case LSR2interrupted:
//		cout << "[SMZ] -  Messung fertig." << endl;
//		actions->stopFB();
//		break;
//	}
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

