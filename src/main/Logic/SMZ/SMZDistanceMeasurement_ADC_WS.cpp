/*
 * SMZDistanceMeasurement_ADC_WS.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZDistanceMeasurement_ADC_WS.h"

void  SMZDistanceMeasurement_ADC_WS::entry(){
	actions->ledQ1On();
}

void SMZDistanceMeasurement_ADC_WS::exit(){
}

void SMZDistanceMeasurement_ADC_WS::doAction(int event, _pulse msg){

	switch(event){
	case LSAinterrupted:
		//Starte Zeitmessung für Wegstrecke von LSA zu ADC
		time1=0.0;
		tstart = 0.0;
		tstart = clock();

		actions->startFB();
		actions->ledQ1Off();
		break;

   case ADC_WK_IN_HM:
		//Stoppe Zeitmessung und speichere in WSAData
	   time1 += clock() - tstart;
	   //Scaliere Sekunden
	   time1 = time1/CLOCKS_PER_SEC;

	   wsa_data->setDistance_LSA_ADC(time1);
	   actions->ledQ1On();

	   //Zeitmessung ADC zu LSS
	   time1 = 0;
	   tstart = 0.0;
	   tstart = clock();

	   actions->moveSlower();
	   break;

   case ADC_SAMPLE_VALUE:
	   //ADC auslesen und abspeichern
	   if(wsa_data->getDistance_FWS_ADC()!= 0){
		   wsa_data->setDistance_WS_ADC(msg.value.sival_int);
	   }else{
		   wsa_data->setDistance_FWS_ADC(msg.value.sival_int);
	   }
	   break;

   case	ADC_WK_NIN_HM:
	   actions->moveFaster();
	   break;

   case LSSinterrupted:
	   time1 += clock() - tstart;
	   time1 = time1/CLOCKS_PER_SEC;
	   wsa_data->setDistance_ADC_LSS(time1);

	   //Zeitmessung LSS zu LSE
	   time1 = 0;
	   tstart = 0.0;
	   tstart = clock();
	   break;

   case LSEinterrupted:
	   time1 += clock() - tstart;
	   time1 = time1/CLOCKS_PER_SEC;

	   wsa_data->setDistance_LSS_LSE(time1);
	   actions->stopFB();

	   //Wenn 2 WS gemessen wurde, State Machine fertig
	   if(wsa_data->getDistance_WS_ADC() != 0 && wsa_data->getDistance_FWS_ADC()){
		   exit();
	   }else{
		   break;
	   }
	}
}




