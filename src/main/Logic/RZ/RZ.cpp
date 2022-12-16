/*
 * RZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "RZ.h"
#include "../SMZ/SMZ.h"


void RZ::entry() {

	actions->greenOn(contextData->disp->getConnectionID());
	actions->yellowOff(contextData->disp->getConnectionID());
	actions->redOff(contextData->disp->getConnectionID());
	printf("---in rz entry");
}

void RZ::exit() {

}

/**
 * Ruhezustand
 */
void RZ::doAction(int event){

	switch (event) {
		//Starte Betriebszustand
		case STRinterrupted:
			exit();
			new(this) BZ;
			entry();
			break;
		//Starte Servicemode
		case STR_SMZ:
			exit();
			new (this) SMZ;
			entry();
			break;
		}
}







