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
	wsa_data->distance_FWS_ADC = distanceMeasurementWS();
	wsa_data->distance_WS_ADC = distanceMeasurementWS();
	wsa_data->sorterTyp = determineSorter();

	_pulse pulseMsg;
				//Warte auf WS
				while(true){
					int recvid = MsgReceivePulse(myChannel, &pulseMsg, sizeof(_pulse), nullptr);

					if (recvid < 0) {
						perror("MsgReceivePulse failed!");
					}

					if (recvid == 0) {
						//Messe Abstand WS -> ADC
						switch (pulseMsg.code) {
						case LSA1 :
							break;
						}
					}
				}
}

/**
 * Gemessene Höhen und Timer zurücksetzen
 */
void SMZCalibration::clearThresholds(){

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
