/*
 * SMZCalibration.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZMesseGrundhoehe.h"

#include "SMZwsFlach.h"

void SMZMesseGrundhoehe::entry(){
	actions->yellowLightBlinking();
	cout << "[SMZ] - Bereit grundhoehe zu messen" << endl;

	//clearThresholds();

//	exit();
//	new(this)SMZDistanceMeasurement_ADC_FB;
//	entry();


}

void SMZMesseGrundhoehe::exit(){
}

void SMZMesseGrundhoehe::doAction(int event, _pulse msg){

	switch(event){
	case LSA1interrupted:
		cout << "[SMZ] - Messe Grundhoehe ..." << endl;
		actions->yellowOn();
		actions->startSMZ_hoehe(0);
		actions->startFB();
		break;
	case LSR1interrupted:
		actions->stopFB();
		cout << "[SMZ] - Messung fertig" << endl;

		break;
	case STRinterrupted:
		exit();
		new(this) SMZwsFlach;
		entry();
		break;
	}


}

/**
 * Gemessene Höhen und Timer zurücksetzen
 */
void SMZMesseGrundhoehe::clearThresholds(){

}
