/*
 * SMZTestingWS.cpp
 *
 *  Created on: 18.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZTestingWS.h"

void SMZTestingWS::entry(){
	actions->greenOn();
}

void SMZTestingWS::exit(){
	actions->greenOff();
	actions->stopFB();
}

void SMZTestingWS::doAction(int event, _pulse msg){

	switch(event){
	//State Machine beenden
	case STPinterrupted:
		exit();
		new (this) RZ;
		break;

	case LSAinterrupted:
		actions->startFB();
		actions->ledQ1On();
		wkTest = false;
		break;

	case LSEinterrupted:
		actions->stopFB();
		break;

	case LSSinterrupted:
		if(wkTest){
			actions->durchlassen();
		}else{
			actions->aussortieren();
		}
		break;

	case ADC_WK_IN_HM:
		actions->ledQ1Off();
		break;

	case ADC_SAMPLE_VALUE:
		//In WS Daten speichern
		break;

	case MTDinterrupted:
		wkTest = true;
		break;
	}
}

