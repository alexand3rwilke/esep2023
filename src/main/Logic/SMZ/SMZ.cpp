/*
 * SMZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "SMZ.h"

void SMZ :: entry(){
	printf("SMZ entry\n");
	actions->greenLightBlinking();

	substate = new SMZ();

	//substate->entry();

}

void SMZ :: exit(){
	actions->greenOff();
}

/**
 * Wahl Kalibrieren oder Testen
 */
void SMZ :: doAction(int event, _pulse msg){

	switch (event) {

	//Choose calibrationmode
	case STRinterrupted:
		//substate->exit();
		new(substate)SMZCalibration;
		substate->setActions(actions);
		substate->setContextData(contextData);
		substate->entry();
		break;

	//Choose testmode
	case STPinterrupted:
		//substate->exit();
		new(substate)SMZTesting;
		substate->setActions(actions);
		substate->setContextData(contextData);
		substate->entry();
		break;

	case ESTPinterrupted:
		substate->exit();
		//substate = null;
		exit();
		new(this) ESZ;
		entry();
		break;
	default:
		substate->doAction(event,msg);
	}

}
