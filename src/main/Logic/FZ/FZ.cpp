/*
 * FZ.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "FZ.h"



void FZ:: entry(){
	actions->ampAllOff();
	actions->redLightBlinking();
	actions->stopFB();
	substate = new FAUZ();
	substate->setActions(actions);
	substate->setContextData(contextData);
	substate->entry();

}
void FZ:: exit(){
	actions->ampAllOff();
	substate = NULL;

}
void FZ::doAction(int event, _pulse msg){
	switch(event){
	case LSR1notInterrupted:
		substate->doAction(LSR1notInterrupted, msg);
		break;
	case LSR2notInterrupted:
		substate->doAction(LSR2notInterrupted, msg);
		break;
//	case LSR1interrupted:
//		contextData->setRampe1Voll(true);
//		break;
//	case LSR2interrupted:
//		contextData->setRampe2Voll(true);
//		break;

	case RUTSCHE_1_LEER:
		substate->doAction(RUTSCHE_1_LEER, msg);
		break;
	case RUTSCHE_2_LEER:
		substate->doAction(RUTSCHE_2_LEER, msg);
		break;
	case ESTP1interrupted:
		exit();
		new (this) ESZ;
		entry();
		break;
	case ESTP2interrupted:
		exit();
		new (this) ESZ;
		entry();
		break;
	case RSTinterrupted:
		substate->doAction(RSTinterrupted, msg);
		break;
	case FEHLER_OK:
		exit();
		new (this) BZ;
		entry();
	}

}

