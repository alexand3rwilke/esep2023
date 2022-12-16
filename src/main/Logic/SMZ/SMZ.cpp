/*
 * SMZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "SMZ.h"

void SMZ :: entry(){
	actions->greenLightBlinking(wsa_data->dispID);
	substate = NULL;
}

void SMZ :: exit(){

//	actions->greenLightBlinkingOff(1);

}

/**
 * Wahl Kalibrieren oder Testen
 */
void SMZ :: doAction(int event){

					switch (event) {
					//Choose calibrationmode

					case STRinterrupted:
						exit();
						new (this)SMZCalibration;
						break;

					//Choose testmode
					case STPinterrupted:
						exit();
						new(this)SMZTesting;
						entry();
						break;
					}
				}
