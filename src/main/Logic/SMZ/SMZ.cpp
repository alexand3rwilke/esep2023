/*
 * SMZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "SMZ.h"

void SMZ :: entry(){
	printf("SMZ entry \n");
	actions->greenLightBlinking();
	substate = new SMZMesseGrundhoehe();
	substate->setActions(actions);
	substate->setContextData(contextData);
	substate->entry();

}

void SMZ :: exit(){
}

/**
 * Wahl Kalibrieren oder Testen
 */
void SMZ :: doAction(int event, _pulse msg){

	substate->doAction(event,msg);
	switch (event) {

	//Choose calibrationmode
//	case STRinterrupted:
//		exit();
//		new(substate)SMZMesseGrundhoehe;
//		entry();
//		break;

	//Choose testmode
	case STPinterrupted:
		exit();
//		new(substate)SMZDistanceMeasurement_ADC_WS;
		new (this) RZ;
		entry();
		break;
	case RSTinterrupted:
		substate->exit();
		new(substate)SMZDistanceMeasurement_ADC_WS;
		substate->entry();
		break;

	case ESTP1interrupted:
		exit();
		new(this) ESZ;
		entry();
		break;

	case ESTP2interrupted:
		exit();
		new(this) ESZ;
		entry();
		break;
	}
}
