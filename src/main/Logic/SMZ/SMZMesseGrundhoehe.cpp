/*
 * SMZCalibration.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZMesseGrundhoehe.h"

#include "WarteAufFlachesWS.h"

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
		actions->startSMZ_hoehe();
		actions->startFB();
		break;
	case STRinterrupted:
		exit();
		new(this) Warte_Auf_Flaches_WS;
		entry();
	}


}

/**
 * Gemessene Höhen und Timer zurücksetzen
 */
void SMZMesseGrundhoehe::clearThresholds(){

//	wsa_data->setSorterTyp(0);
//	wsa_data->setDistance_FB_ADC(0);
//	wsa_data->setDistance_FWS_ADC(0);
//	wsa_data->setDistance_WS_ADC(0);
//	wsa_data->setDistance_LSA_ADC(0);
//	wsa_data->setDistance_ADC_LSS(0);
//	wsa_data->setDistance_LSS_LSE(0);
//
//	exit();
//	new(this)SMZDistanceMeasurement_ADC_FB;
//	entry();

}
