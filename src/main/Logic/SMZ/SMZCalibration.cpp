/*
 * SMZCalibration.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZCalibration.h"

void SMZCalibration::entry(){
	doAction();

}

void SMZCalibration::exit(){

}

void SMZCalibration::doAction(){

	clearThresholds();
	wsa_data->distance_FB_ADC = distanceMeasurementFB();
	wsa_data->sorterTyp = determineSorter();
//
//	switch (pulseMsg.code) {
//		case LSA1 : if(wsa_data->distance_FWS_ADC != 0){
//			wsa_data->distance_FWS_ADC = distanceMeasurementWS();
//			break;
//		}else{
//							wsa_data->distance_WS_ADC = distanceMeasurementWS();
//							break;
//						}
//						case LSS1 :
//							break;
//
//						case LSE1:
//							break;
//						}
//

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

/**
 * Abstand FB und ADC bestimmen
 */
int SMZCalibration::distanceMeasurementFB(){
	int measurement;

	return measurement;
}

/**
 * Ermittle den Aussortierertyp
 */
int SMZCalibration::determineSorter(){
	int sorter;

	return sorter;
}

/**
 * Abstand WS und ADC bestimmen
 */
int SMZCalibration::distanceMeasurementWS(){




	//Zurück in den RZ
	//new(this)RZ;
}
