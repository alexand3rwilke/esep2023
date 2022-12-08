
/*
 * ADCService.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 *
 */
#include "ADC_Service.h"
using namespace std;



TSCADC tsc;
ADC adc(tsc);


ADC_Service::ADC_Service(Dispatcher *dispatcher) {

	disp = dispatcher;

	dispId  = dispatcher->getConnectionID();
	ADCServiceThread  = new std::thread([this]() {adcService();});


}

ADC_Service::~ADC_Service() {


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

				// run 4ever
				 while (true) {

					 	 //
					 int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

					 		if (recvid < 0) {
					 			perror("MsgReceivePulse failed!");
					 			exit(EXIT_FAILURE);
					 		}

					 		adc.sample();


					 		// send adc value to dispathcer
					 		switch(pulse.code){
					 		case ADC_SAMLING_FINISHED:  MsgSendPulse(dispId, -1, ADC_SAMPLE_VALUE, pulse.value.sival_int);


					 									if(pulse.value.sival_int < 2700) {
					 									MsgSendPulse(dispId, -1, ADC_WK_IN_HM, pulse.value.sival_int);

					 									}
					 									break;


					 		// sample adc data
					 		case ADC_START_SAMPLE:		adc.sample();
					 									break;

					 		}

				 }

}
