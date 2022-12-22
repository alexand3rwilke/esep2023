/*
 * SMZTestingWS.cpp
 *
 *  Created on: 18.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZTestingWS.h"

void SMZTestingWS::entry(){

	//LEDs testen
	actions->ledQ1Off();//ist q2 off
	//actions->ledQ2Off();
	sleep(2);
	actions->ledQ1On();
	//actions->ledQ2On();
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

	case LSA1interrupted:
		actions->startFB();
		actions->ledQ1Off();
		wkTest = false;
		break;

	case LSE1interrupted:
		actions->stopFB();
		break;

	case LSS1interrupted:
		if(wkTest){
			actions->durchlassen();
		}else{
			actions->aussortieren();
			sleep(2);
			actions->stopFB();
		}
		break;

	case ADC_WK_IN_HM:
		actions->ledQ1On();
		break;

	case ADC_WK_NIN_HM:
		break;

	case ADC_START_SINGLE_SAMPLE:
		printf("!!!");
		break;

	case MTD1interrupted:
		wkTest = true;
		break;
	}
}

