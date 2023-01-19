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
	cout << "Zum starten LSA unterbrechen" << endl;
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

		actions->yellowOn();
		actions->startFB();
		actions->startSMZ_hoehe(0);
		cout << "[SMZ] - Messe Grundhoehe ..." << endl;
		break;
	case LSA2interrupted:
		actions->yellowOn();
		actions->startFB();
		actions->startSMZ_hoehe(0);
		cout << "[SMZ] - Messe Grundhoehe ..." << endl;
			break;
	case LSR1interrupted:
		actions->stopFB();
		cout << "[SMZ] - Messung fertig" << endl;

		break;
	case LSR2interrupted:
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
