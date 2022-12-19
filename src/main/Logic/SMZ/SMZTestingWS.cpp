/*
 * SMZTestingWS.cpp
 *
 *  Created on: 18.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZTestingWS.h"

void SMZTestingWS::entry(){
	actions->greenOn();

	//LEDs testen
	actions->ledQ1Off();
	actions->ledQ2Off();
	sleep(2);
	actions->ledQ1On();
	actions->ledQ2On();
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
		actions->ledQ1Off();
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


//	case ADC_WK_IN_HM:
//		actions->ledQ1On();
//		break;

	case ADC_SAMPLE_VALUE:
		printf("!!!");
		//In WS Daten speichern
		break;

	case MTDinterrupted:
		wkTest = true;
		break;
	}
}

