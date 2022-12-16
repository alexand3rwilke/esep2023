/*
 * SMZCalibration.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZCalibration.h"

void SMZCalibration::entry(){
	clearThresholds();
	//wsa_data->sorterTyp = act->getSorter();
	exit();
	new (this) SMZDistanceMeasurement_ADC_FB;
	entry();
}

void SMZCalibration::exit(){
}

void SMZCalibration::doAction(int event){
}

/**
 * Gemessene Höhen und Timer zurücksetzen
 */
void SMZCalibration::clearThresholds(){
	wsa_data->sorterTyp = 0;
	wsa_data->distance_FB_ADC = 0;
	wsa_data->distance_FWS_ADC = 0;
	wsa_data->distance_WS_ADC = 0;

	wsa_data->distance_LSA_ADC = 0;
	wsa_data->distance_ADC_LSS = 0;
	wsa_data->distance_LSS_LSE = 0;

}
