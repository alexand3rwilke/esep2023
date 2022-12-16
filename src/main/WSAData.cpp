/*
 * WSAData.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "WSAData.h"

WSAData::WSAData(Dispatcher *dispatcher){
	disp = dispatcher;
	dispID  = disp->getConnectionID();
	sorterTyp = 0;
	distance_FB_ADC = 0;
	distance_FWS_ADC = 0;
	distance_WS_ADC = 0;

	distance_LSA_ADC = 0;
	distance_ADC_LSS = 0;
	distance_LSS_LSE = 0;
}

WSAData::~WSAData(){

}



