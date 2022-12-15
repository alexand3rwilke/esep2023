/*
 * SMZDistanceMeasurement_ADC_WS.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Hendrik Marquardt
 */

#include "SMZDistanceMeasurement_ADC_WS.h"

void  SMZDistanceMeasurement_ADC_WS::entry(){
	actions->ledQ1On(wsa_data->dispID);
}

void SMZDistanceMeasurement_ADC_WS::exit(){
	actions->greenLightBlinkingOff(wsa_data->dispID);
}

void SMZDistanceMeasurement_ADC_WS::doAction(int event){

	switch(event){
	case LSAinterrupted:
		//Starte Zeitmessung für Wegstrecke von LSA zu ADC
		time1=0.0;
		tstart = 0.0;
		tstart = clock();

		actions->startFB(wsa_data->dispID);
		actions->ledQ1Off(wsa_data->dispID);
		break;

   case ADC_WK_IN_HM:
		//Stoppe Zeitmessung und speichere in WSAData
	   time1 += clock() - tstart;
	   //Scaliere Sekunden
	   time1 = time1/CLOCKS_PER_SEC;

	   wsa_data->distance_LSA_ADC = time1;
	   actions->ledQ1On(wsa_data->dispID);

	   //Zeitmessung ADC zu LSS
	   time1 = 0;
	   tstart = 0.0;
	   tstart = clock();

	   actions->moveSlower(wsa_data->dispID);
	   //TODO: ADC auslesen
	   if(wsa_data->distance_FWS_ADC != 0){
		   //wsa_data->distance_WS_ADC = ADCAuslesen();
	   }else{
		   //wsa_data->distance_FWS_ADC = ADCAuslesen();
	   }
	   break;

   case	ADC_WK_NIN_HM:
	   actions->moveFaster(wsa_data->dispID);
	   break;

   case LSSinterrupted:
	   time1 += clock() - tstart;
	   time1 = time1/CLOCKS_PER_SEC;
	   wsa_data->distance_ADC_LSS = time1;

	   //Zeitmessung LSS zu LSE
	   time1 = 0;
	   tstart = 0.0;
	   tstart = clock();
	   break;

   case LSEinterrupted:
	   time1 += clock() - tstart;
	   time1 = time1/CLOCKS_PER_SEC;

	   wsa_data->distance_LSS_LSE = time1;
	   actions->stopFB(wsa_data->dispID);

	   //Wenn erst ein WS gemessen wurde, dann mach noch eine Messung
	   if(wsa_data->distance_WS_ADC != 0){
		   exit();
	   }else{
		   break;
	   }
	}
}




