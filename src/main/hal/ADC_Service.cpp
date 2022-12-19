
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

int counter = 0;
bool isInterrupted = false;

ADC_Service::ADC_Service(Dispatcher *dispatcher) {

	disp = dispatcher;
	dispId  = dispatcher->getConnectionID();
	ADCServiceThread  = new std::thread([this]() {adcService();});
	ADCInterruptServiceThread  = new std::thread([this]() {adcService();});
	ADCServiceThread  = new std::thread([this]() {adcInterruptService();});
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

			events = {ADC_START_SAMPLE};
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
					 		switch(pulse.code){
					 		case ADC_SAMLING_FINISHED:

					 			//Wenn noch keine Distanzmessung hinterlegt wurde
					 			if(&wsa_data->distance_FB_ADC == 0){
					 			MsgSendPulse(dispId, -1, ADC_SAMPLE_VALUE, pulse.value.sival_int);

					 			}else if(pulse.value.sival_int < 2700 && !isInterrupted){
								isInterrupted = true;
								counter++;
								printf("werkstueck in hoehenmessung  \n");
								MsgSendPulse(dispId, -1, ADC_WK_IN_HM, pulse.value.sival_int);
								}

								else if(pulse.value.sival_int > 2700 && isInterrupted){
									isInterrupted = false;
									MsgSendPulse(dispId, -1, ADC_WK_NIN_HM, pulse.value.sival_int);
									//TODO: Wert der versendet werden soll, muss hier noch zwischendurch gespeichert und weiterverarbeitet werden
									//TODO: oder Wert kann schon mit erster WS-Erkennung verschickt werden ? Testen und Werte ansehen.
									//Möglicherweise ist die erste Messung schnell genug um nicht über den rand des WS zu springen.
									//Versende den Wert der Messung
									MsgSendPulse(dispId, -1, ADC_SAMPLE_VALUE, pulse.value.sival_int);
								}
								break;

					 		case ADC_START_SAMPLE:		adc.sample();
					 									break;
					 		}
				 }
}





void ADC_Service::adcService() {

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

			events = {ADC_START_SAMPLE};
			disp->registerForEventWIthConnection(events, conID);

			_pulse pulse;

				 while (true) {

					 int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

					 		if (recvid < 0) {
					 			perror("MsgReceivePulse failed! - ADC_Service");
					 			exit(EXIT_FAILURE);
					 		}
					 		// send adc value to dispathcer
					 		switch(pulse.code){


					 		case ADC_SAMLING_FINISHED:

					 			MsgSendPulse(dispId, -1, ADC_SAMPLE_VALUE, pulse.value.sival_int);
								break;

					 		case ADC_START_SAMPLE:		adc.sample();
					 									break;
					 		}
				 }
}
