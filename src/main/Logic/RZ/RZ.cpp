/*
 * RZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "RZ.h"
#include "../SMZ/SMZ.h"


void RZ::entry() {

	cout << "\n  rz entry\n" << endl;
	//actions->greenOff();
	//actions->yellowOff();
	actions->ampAllOff();
}

void RZ::exit() {

}


/**
 * Ruhezustand
 */

void RZ::doAction(int event, _pulse msg){
	switch (event) {
		//Starte Betriebszustand
		case STRinterrupted:
			printf("\n wechsel zu BZ \n");
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
		case ESTP1interrupted:
			cout << "Estp in RZ \n" << endl;
			exit();
			new(this) ESZ;
			entry();
			break;


		case ESTP2interrupted:
			cout << "Estp in RZ \n" << endl;
			exit();
			new(this) ESZ;
			entry();
			break;
	}
}


void RZ::estp(){
	exit();
	new(this) ESZ;
	entry();

}
