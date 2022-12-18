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

void SMZDistanceMeasurement_ADC_FB::doAction(int event, _pulse msg){
	//Höhe FB zu ADC messen
	switch(event){

		case ADC_SAMPLE_VALUE:
			//TODO: ADC auslesen und in wsaData abspeichern
			//wsa_data->distance_FB_ADC = adc->sample();
			exit();
			new (this) SMZDistanceMeasurement_ADC_WS;
			entry();
	}
}


