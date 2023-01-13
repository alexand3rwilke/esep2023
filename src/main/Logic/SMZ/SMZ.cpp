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
		new(this)SMZTesting;
		entry();
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
