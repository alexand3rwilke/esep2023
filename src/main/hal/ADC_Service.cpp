
/*
 * ADCService.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 *
 */
#include "ADC_Service.h"

TSCADC tsc;
ADC adc(tsc);
ADC adcSingle(tsc);


int counter = 0;
bool isInterrupted = false;

ADC_Service::ADC_Service(Dispatcher *dispatcher) {
//
	disp = dispatcher;
	dispId  = dispatcher->getConnectionID();
	ADCInterruptServiceThread  = new std::thread([this]() {adcInterruptService();});



}

ADC_Service::~ADC_Service() {


}

void ADC_Service::adcInterruptService() {

	ThreadCtl(_NTO_TCTL_IO, 0);
	/* ### Create channel ### */
			int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
			if (chanID < 0) {
				perror("Could not create a channel!\n");

			}

			int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
			if (conID < 0) {
				perror("Could not connect to channel!");

			}

			// schicke pulse mit sampling don wenn sampling fertig ist an adc_service selber
			adc.registerAdcISR(conID,ADC_SAMLING_FINISHED);



			events = {ADC_START_SAMPLE, ADC_SAMLING_FINISHED};

			//events = {ADC_START_SAMPLE};

			disp->registerForEventWIthConnection(events, conID);

			_pulse pulse;

				 while (true) {

					 adc.sample();
					 int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

					 		if (recvid < 0) {
					 			perror("MsgReceivePulse failed! - ADC_Service");
					 			exit(EXIT_FAILURE);
					 		}
					 		// send adc value to dispathcer
					 		//switch(pulse.code){
					 		//case ADC_SAMLING_FINISHED:

					 			//Wenn noch keine Distanzmessung hinterlegt wurde für FB_ADC Messung
//					 			if(&wsa_data->distance_FB_ADC == 0){
//					 			MsgSendPulse(dispId, -1, ADC_WK_IN_HM, pulse.value.sival_int);
//					 			}
					 		//sleep(2);
					 		aktuelleHoehe = pulse.value.sival_int;
					 			//WS in Höhenmessung
					 		 //if(aktuelleHoehe < MIN_HOEHE && aktuelleHoehe > MAX_HOEHE &&!isInterrupted){
					 		if(aktuelleHoehe < MIN_HOEHE && aktuelleHoehe > MAX_HOEHE &&!isInterrupted){


								isInterrupted = true;

								printf("werkstueck in hoehenmessung %d \n",counter);
								//
								MsgSendPulse(dispId, -1, ADC_WK_IN_HM, aktuelleHoehe);
								}
					 			//WS raus aus Höhenmessung
								else if(aktuelleHoehe > MIN_HOEHE && isInterrupted){
									isInterrupted = false;
									printf("Es wurden %d Messungn beim Höhenmesser gemacht \n",counter);
									// berechne durchschnnit
									MsgSendPulse(dispId, -1, ADC_WK_NIN_HM, aktuelleHoehe);
									//MsgSendPulse(dispId, -1, ADC_SAMLING__VALUE_FINISHED, aktuelleHöhe);
									//printSamples();
									//TODO Hier WK classify starten
									counter = 0;
									samples.clear();
								} else if (isInterrupted){
									samples.push_back(pulse.value.sival_int);
									counter++;
								}

					 			//break;
//					 			switch(pulse.code){
//					 		case ADC_START_SAMPLE:
//					 				adc.sample();
//					 				break;
					 		//}
				 }
}

int ADC_Service::classifyWK() {
	int i = 0;
	int max = samples.front();
	int letzterWert = samples.front();
	int diff = 0;
	int maxDiff = 0;
	

for(int s: samples){

		if(letzterWert > s) {
			diff = letzterWert - s;
		} else {

			diff = s - letzterWert;
		}


	if (s > max) {
		max = s;
	}
	if(diff > maxDiff) {
		maxDiff = diff;

	}

	}

	// hier damit WK klassifizieren


	if(max < 2500 ) {
		return WK_FLACH;
	}

	else if((max > 2500 && max < 2800) && maxDiff > 50) {

		return WK_Bohrung;
	}


	else if((max > 2500 && max < 2800) && maxDiff < 50) {

		return WK_Normal;
	}

	return WK_UNDEFINED;




}

void ADC_Service::printSamples(){
	int i=1;
	for(int s: samples){
		cout << i << ". höhe:"<< s << endl;
		//printf("%d. höhe: %d \n ",i,s);
		i++;
	}
}





