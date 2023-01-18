/*
 * SMZDistanceMeasurement_ADC_WS.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Hendrik Marquardt
 */

#include "../../Imports.h"


#include "SMZDistanceMeasurement_ADC_WS.h"

void  SMZDistanceMeasurement_ADC_WS::entry(){
	 cout <<"Sind in der Distanz Messung" << endl;
	actions->yellowOn();
	gesamtZeit= 0.0;

}

void SMZDistanceMeasurement_ADC_WS::exit(){
}

void SMZDistanceMeasurement_ADC_WS::doAction(int event, _pulse msg){

	switch(event){
		case LSA1interrupted:


			actions->startFB();
			//actions->ledQ1Off();
			break;

		case LSA1notInterrupted:

			start_stopuhr();
			break;


	   case ADC_WK_IN_HM:

		   //Scaliere Sekunden
		   zeit = stopp_stopuhr();
		   cout <<"Zeit von LSA bis ADC: " << zeit << endl;
//
		   //wsa_data->setDistance_LSA_ADC(time1);
		   actions->ledQ1On();

		   start_stopuhr();

		   actions->moveSlower();
		   break;

	   case ADC_SAMLING_FINISHED:
		   //ADC auslesen und abspeichern
		   if(wsa_data->getDistance_FWS_ADC()!= 0){
			   wsa_data->setDistance_WS_ADC(msg.value.sival_int);
		   }else{
			   wsa_data->setDistance_FWS_ADC(msg.value.sival_int);
		   }
		   break;

	   case	ADC_WK_NIN_HM:
		   zeit = stopp_stopuhr();
		   cout <<"Zeit im ADC (Slow-Modus): " << zeit << endl;
		   actions->moveFaster();
		   start_stopuhr();
		   break;

	   case LSS1interrupted:
		   zeit = stopp_stopuhr();
		   cout <<"ADC bis LSS: " << zeit << endl;
		   actions->durchlassen();

		   //wsa_data->setDistance_ADC_LSS(time1);

		 start_stopuhr();
		   break;

	   case LSE1interrupted:
		   zeit = stopp_stopuhr();
		   cout <<"LSS bis LSE: " << zeit << endl;


		   cout << endl << "Gesamtzeit: " << gesamtZeit << endl;
		   //wsa_data->setDistance_LSS_LSE(zeit);
		   actions->stopFB();
		   break;

	   case LSE1notInterrupted:
		   exit();
		   entry();
//
//		   //Wenn 2 WS gemessen wurde, State Machine fertig
//		   if(wsa_data->getDistance_WS_ADC() != 0 && wsa_data->getDistance_FWS_ADC()){
//			   exit();
//		   }else{
//
//		   }
//		   break;
	}
}

void SMZDistanceMeasurement_ADC_WS::start_stopuhr(){

	endZeit = 0.0;
	startZeit = 0.0;
	startZeit = clock();
	warStartSchon= true;

}

double SMZDistanceMeasurement_ADC_WS::stopp_stopuhr(){
	if(warStartSchon){
		warStartSchon=false;
		endZeit = clock() - startZeit;
		endZeit = endZeit/CLOCKS_PER_SEC;
		gesamtZeit = gesamtZeit + endZeit;
		return endZeit;
	}else {
		return -5;
	}

}

//
//#include "SMZDistanceMeasurement_ADC_WS.h"
//
//void  SMZDistanceMeasurement_ADC_WS::entry(){
//	actions->greenOn();
//}
//
//void SMZDistanceMeasurement_ADC_WS::exit(){
//	actions->ampAllOff();
//}
//
//void SMZDistanceMeasurement_ADC_WS::doAction(int event, _pulse msg){
//
//	switch(event){
//	case LSA1interrupted:
//		//Starte Zeitmessung für Wegstrecke von LSA zu ADC
//		time1=0.0;
//		tstart = 0.0;
//		tstart = clock();
//
//		actions->startFB();
//		actions->ledQ1Off();
//		break;
//
//   case ADC_WK_IN_HM:
//		//Stoppe Zeitmessung und speichere in WSAData
//	   time1 += clock() - tstart;
//	   //Scaliere Sekunden
//	   time1 = time1/CLOCKS_PER_SEC;
//
//	   wsa_data->setDistance_LSA_ADC(time1);
//	   actions->ledQ1On();
//
//	   //Zeitmessung ADC zu LSS
//	   time1 = 0;
//	   tstart = 0.0;
//	   tstart = clock();
//
//	   actions->moveSlower();
//	   break;
//
//   case ADC_SAMPLE_VALUE:
//	   //ADC auslesen und abspeichern
//	   if(wsa_data->getDistance_FWS_ADC()!= 0){
//		   wsa_data->setDistance_WS_ADC(msg.value.sival_int);
//	   }else{
//		   wsa_data->setDistance_FWS_ADC(msg.value.sival_int);
//	   }
//	   break;
//
//   case	ADC_WK_NIN_HM:
//	   actions->moveFaster();
//	   break;
//
//   case LSS1interrupted:
//	   time1 += clock() - tstart;
//	   time1 = time1/CLOCKS_PER_SEC;
//	   //wsa_data->setDistance_ADC_LSS(time1);
//
//	   //Zeitmessung LSS zu LSE
//	   time1 = 0;
//	   tstart = 0.0;
//	   tstart = clock();
//	   break;
//
//   case LSE1interrupted:
//	   time1 += clock() - tstart;
//	   time1 = time1/CLOCKS_PER_SEC;
//
//	   wsa_data->setDistance_LSS_LSE(time1);
//	   actions->stopFB();
//	   exit();
//	   new (this) RZ;
//	   entry();
//
//	   //Wenn 2 WS gemessen wurde, State Machine fertig
//	   if(wsa_data->getDistance_WS_ADC() != 0 && wsa_data->getDistance_FWS_ADC()){
//
//	   }else{
//		   break;
//	   }
//	}
//}




