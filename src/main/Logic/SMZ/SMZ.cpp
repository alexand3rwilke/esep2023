/*
 * SMZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "SMZ.h"

void SMZ :: entry(){
	printf("SMZ entry");
	actions->greenLightBlinking();
}

void SMZ :: exit(){
}

/**
 * Wahl Kalibrieren oder Testen
 */
void SMZ :: doAction(int event, _pulse msg){

	switch (event) {

	//Choose calibrationmode
	case STRinterrupted:
		exit();
		new(this)SMZCalibration;
		entry();
		break;

	//Choose testmode
	case STPinterrupted:
		exit();
		new(this)SMZTestingWS;
		entry();
		break;

	case ESTPinterrupted:
		exit();
		new(this) ESZ;
		entry();
		break;
	}
}
