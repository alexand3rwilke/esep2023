/*
 * SMZCalibration.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZCalibration.h"

void SMZCalibration::entry(){
	clearThresholds();
	exit();
	new(this)SMZDistanceMeasurement_ADC_FB;
	entry();
}

void SMZCalibration::exit(){
}

void SMZCalibration::doAction(int event, _pulse msg){
}

/**
 * Gemessene Höhen und Timer zurücksetzen
 */
void SMZCalibration::clearThresholds(){
	wsa_data->setSorterTyp(0);
	wsa_data->setDistance_FB_ADC(0);
	wsa_data->setDistance_FWS_ADC(0);
	wsa_data->setDistance_WS_ADC(0);
	wsa_data->setDistance_LSA_ADC(0);
	wsa_data->setDistance_ADC_LSS(0);
	wsa_data->setDistance_LSS_LSE(0);
}
