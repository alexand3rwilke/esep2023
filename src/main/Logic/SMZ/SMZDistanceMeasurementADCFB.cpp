/*
 * SMZDistanceMeasurement.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZDistanceMeasurementADCFB.h"

void SMZDistanceMeasurement_ADC_FB::entry(){

}

void SMZDistanceMeasurement_ADC_FB::exit(){

}

void SMZDistanceMeasurement_ADC_FB::doAction(int event){
	//Höhe FB zu ADC messen
	switch(event){

	   case ADC_WK_IN_HM:
		   actions->moveSlower(wsa_data->dispID);
		   break;

	   case	ADC_WK_NIN_HM:
		   actions->moveFaster(wsa_data->dispID);
		   break;

		case ADC_SAMPLE_VALUE:
			//TODO: ADC auslesen und in wsaData abspeichern
			//adc->sample();
			exit();
			new (this) SMZDistanceMeasurement_ADC_WS;
			entry();
	}
}


