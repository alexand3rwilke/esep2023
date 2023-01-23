
/*
 * ADCService.cpp
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 *
 */
#include "ADC_Service.h"

#include <cmath>
#include <fstream>



TSCADC tsc;
ADC adc(tsc);
ADC adcSingle(tsc);


int counter = 0;
bool isInterrupted = false;

ADC_Service::ADC_Service(Dispatcher *dispatcher) {

	disp = dispatcher;
	dispId  = dispatcher->getConnectionID();
	ADCInterruptServiceThread  = new std::thread([this]() {adcInterruptService();});
}

ADC_Service::~ADC_Service() {
	delete disp;
	delete ADCInterruptServiceThread;
	delete wsa_data;
}

void ADC_Service::adcInterruptService() {

	ThreadCtl(_NTO_TCTL_IO, 0);
	chanID = ChannelCreate(0);
	if (chanID < 0) {
		perror("Could not create a channel!\n");

	}

	conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); 
	if (conID < 0) {
		perror("Could not connect to channel!");
	}
	adc.registerAdcISR(conID,ADC_SAMLING_FINISHED);

	events = {ADC_START_SAMPLE, ADC_SAMLING_FINISHED, START_SMZ, LSR1interrupted, LSR2interrupted};
	disp->registerForEventWIthConnection(events, conID);

	_pulse pulse;

	while (true) {

		adc.sample();
		int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

		if (recvid < 0) {
			perror("MsgReceivePulse failed! - ADC_Service");
			exit(EXIT_FAILURE);
		}

		//printf("DIESE HÖHE HAT DEN ADC GETRIGGERT: %d \n",pulse.value.sival_int);
		aktuelleHoehe = pulse.value.sival_int;
		if(pulse.code == START_SMZ){

			SMZ_checkHoehe = true;
			ws_type = pulse.value.sival_int;
		}

		if(!SMZ_checkHoehe){

			if((aktuelleHoehe < h_grund-150 &&!isInterrupted)&& aktuelleHoehe != 0 ){
				isInterrupted = true;
				MsgSendPulse(dispId, -1, ADC_WK_IN_HM, 0);
		}
		//WS raus aus Höhenmessung
		else if((aktuelleHoehe > h_grund-90 && isInterrupted)&& (counter != 0) && samples.size() > 52){
			isInterrupted = false;
			MsgSendPulse(dispId, -1, ADC_WK_NIN_HM, 0);
			int wkType = classifyWK();
			//cout << "WS TYPE : " << wkType <<endl;
			//printf("WK TYPE : %d",wkType);
			counter = 0;
			samples.clear();
			} else if (isInterrupted){
				samples.push_back(pulse.value.sival_int);
				counter++;
			}
		} else {

			if(ws_type== 0){
				messeGrundhoehe(pulse);
			} else {
				chooseWS();
			}
		}
	}
}

void ADC_Service::messeGrundhoehe(_pulse pulse){

	if(samples.size()  <= 1000){
	samples.push_back(pulse.value.sival_int);
	} else {
		samples.erase(samples.begin());
		int summe=0;
		int max=10000;
		for(int i: samples){
			summe += i;
			if(i<max){
				max =i;
			}
		}
		int tmp = summe / samples.size();
		//cout <<"Es wurden in " << samples.size() << "Messungen der Durchschnitt:"<<  tmp <<"\n" << endl;
		//cout <<"Messungen der Grundhöhe: "<<  tmp <<"\n" << endl;
		//cout <<"Höhste gemessene Grundhöhe:"<<  max <<"\n" << endl;
		h_grund = tmp;
		if(FESTO_TYPE == 1){
			MsgSendPulse(dispId, -1, LSR1interrupted, 0);
		} else if (FESTO_TYPE == 2){
			MsgSendPulse(dispId, -1, LSR2interrupted, 0);
		}
		samples.clear();
		SMZ_checkHoehe = false;
	}
}




int ADC_Service::classifyWK() {


	// remove noise from start and beginning
//	for(int i = 0; i < 10; i++) {
//
//		samples.erase(samples.begin());
//		samples.pop_back();
//	}

	int max = samples.front();
	int min = samples.front();
	int letzterWert = samples.front();
	int diff = 0;
	int maxDiff = 0;
	

//	for(int s: samples){
//
//		if(letzterWert > s) {
//			diff = letzterWert - s;
//		} else {
//			diff = s - letzterWert;
//		}
//
//		if (s > max) {
//			max = s;
//		}
//
//		if (s < min) {
//			min = s;
//		}
//
//
//		if(diff > maxDiff) {
//			maxDiff = diff;
//		}
//
//	}
	int wsHoehenWert = 0;
	if(FESTO_TYPE == 1){
		for (int sample : samples) {
				wsHoehenWert += sample;
			}
		wsHoehenWert = wsHoehenWert / samples.size();

	} else if (FESTO_TYPE == 2){
		int wsHoehenWert = h_grund;
		for (int sample : samples) {
			if(sample < wsHoehenWert && 100 < sample){
				wsHoehenWert = sample;
			}
		}
	}


	

//	printf("MAX: %d \n",max);
//	printf("MIN: %d \n",min);

	if(cmConvertValue_flach ==0){
		cmConvertValue_flach = findCmConverter(21,h_flach);
	}
	if(cmConvertValue_normal == 0){
		cmConvertValue_normal = findCmConverter(25,h_normal);
	}

		printf("WS Wert bei Classify: %d \n",wsHoehenWert);

	if(wsHoehenWert < h_flach + toleranz && wsHoehenWert > h_flach - toleranz) {
		wsHoehenWert = convertToCm(wsHoehenWert, cmConvertValue_flach);
		MsgSendPulse(dispId, -1, WK_FLACH, wsHoehenWert);
		cout << "FLACHES WS ENTDECKT  \n" << endl;
		cout << "Flach: "<< h_flach<< "\n" << endl;
		return WK_FLACH;
	} else if(wsHoehenWert < h_bohrung + toleranz && wsHoehenWert > h_bohrung - toleranz ) {
		wsHoehenWert = convertToCm(wsHoehenWert, cmConvertValue_normal);
		MsgSendPulse(dispId, -1, WK_Bohrung, wsHoehenWert);
		printf("BOHRUNG WS ENTDECKT  \n");
		cout << "Bohrung: "<< h_bohrung<< "\n" << endl;
		return WK_Bohrung;
	}else if(wsHoehenWert < h_normal + toleranz && wsHoehenWert > h_normal - toleranz){
		wsHoehenWert = convertToCm(wsHoehenWert, cmConvertValue_normal);
		MsgSendPulse(dispId, -1, WK_Normal, wsHoehenWert);
		printf("NORMAL WS ENTDECKT  \n");
		cout << "NORMAL: "<< h_normal<< "\n" << endl;
		return WK_Normal;
	} else if(wsHoehenWert < h_metall + toleranz && wsHoehenWert > h_metall - toleranz) {
		wsHoehenWert = convertToCm(wsHoehenWert, cmConvertValue_normal);
		MsgSendPulse(dispId, -1, WK_Bohrung, wsHoehenWert);
		printf("METALL WS ENTDECKT  \n");
		cout << "Bohrung Metall: "<< h_metall<< "\n" << endl;
		return WK_Bohrung;
	}
	MsgSendPulse(dispId, -1, WK_UNDEFINED, 0);
	printf("UNDEFINED WS ENTDECKT  \n");
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

void ADC_Service::chooseWS(){

switch(ws_type){
	case 1:
		h_flach = setWS_hoehe();
		cout << "Flach: "<< h_flach<< "\n" << endl;
		break;

	case 2:
		h_normal = setWS_hoehe();
		cout <<"Normal: "<< h_normal<< "\n" << endl;
		break;

	case 3:
		h_bohrung = setWS_hoehe();
		cout << "Bohrung: "<< h_bohrung<< "\n" << endl;
		break;

	case 4:
		h_metall = setWS_hoehe();
		cout << "Metall: "<< h_metall<< "\n" << endl;


//		 int result = remove("/servicemode.cfg");
//		 cout << result << " ergebnis bei löschen von servicemode file , (0 heisst gelöscht)";
//
//		 cout << result;
//		fstream config;
//		config.open("/hoehenwerte.cfg", ios::out);
//		config << "FLACH " << h_flach <<endl;
//		config << "NORMAL " << h_normal <<endl;
//		config << "BOHRUNG " << h_bohrung <<endl;
//		config << "BOHRUNG_METALL " << h_metall <<endl;
//		config.close();
//		break;


	}
}

int ADC_Service::getGemssenehoehe(int type){
	switch(type){
		case 1:
			cout <<"Flach: "<< h_normal<< "\n" << endl;
			return h_flach;
			//break;

		case 2:
			cout <<"Normal: "<< h_normal<< "\n" << endl;
			return h_normal;
			//break;
		case 3:
			cout << "Bohrung: "<< h_bohrung<< "\n" << endl;
			return h_bohrung;
			//break;

		case 4:
			cout << "Metall: "<< h_metall<< "\n" << endl;
			return h_metall;
			//break;
		default:
			cout << "Die Nummer : "<< type<< "kann als höhe im ADC nicht ausgewählt werden\n" << endl;
			return -1;
		}
}
int ADC_Service::setWS_hoehe(){
	_pulse pulse;

	while(true){
		adc.sample();

		int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

		if(pulse.code == LSR1interrupted && FESTO_TYPE == 1){
			int summe=0;
			for(int s: samples){
				summe += s;
			}
			summe = summe / samples.size();
			cout << "setWS_hoehe: " << summe << endl;

			SMZ_checkHoehe = false;
			samples.clear();
			return summe;
		} else if (pulse.code == LSR2interrupted && FESTO_TYPE == 2){
			int summe=0;
			for(int s: samples){
				summe += s;
			}
			summe = summe / samples.size();
			cout << "setWS_hoehe: " << summe << endl;

			SMZ_checkHoehe = false;
			samples.clear();
			return summe;
		}
		if(pulse.value.sival_int < (h_grund -150)){

			if(!isInterrupted) {
				isInterrupted = true;
				MsgSendPulse(dispId, -1, ADC_WK_IN_HM, 0);
			}
			samples.push_back(pulse.value.sival_int);
		} else if((pulse.value.sival_int > h_grund-400 && isInterrupted)){
				isInterrupted = false;
				MsgSendPulse(dispId, -1, ADC_WK_NIN_HM, 0);
		}
	}
}

double ADC_Service::findCmConverter(double cm, int hoehenTyp){
	double tmp = 0;
	double diff = h_grund - hoehenTyp;
	diff = diff /100;
	tmp = cm / diff;
	return tmp;
}

double ADC_Service::convertToCm(double adcValue, double cmConvertValue){
	float diff = h_grund -adcValue;
	diff = diff / 100;
	double cmResult = diff *cmConvertValue;
	cmResult = cmResult *1000;
	cout << "cmResult: " << cmResult << "- Convert Value \n" << endl;
	int cmTmp = (int)cmResult;
	cout << "cmTmp: " << cmTmp << "- Convert Value (int) \n" << endl;
	return cmResult;
}









