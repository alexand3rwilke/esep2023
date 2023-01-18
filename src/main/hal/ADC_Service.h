
/*
 * ADC_Service.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_ADC_SERVICE_H_
#define SRC_MAIN_HAL_ADC_SERVICE_H_

#include "../Imports.h"
#include "../Dispatcher/Dispatcher.h"
#include "../ADC/ADC.h"
#include "../ADC/Util.h"
#include "../ADC/tscadc_hw.h"
#include "../WSAData.h"

class ADC_Service  {
private:
	int aktuelleHoehe;
	int conID;
	int chanID;
	void printSamples();
	int classifyWK();
	bool SMZ_checkHoehe = false;
	void smz(_pulse pulse);
	int h_grund = 3641;
	int h_flach = 2426; //2426
	int h_normal= 2184; //2184
	int h_bohrung= 2524; //2524
	int h_metall= 2560; //2560
	int toleranz = 40;
	int ws_type=0;
	void chooseWS();
	vector<int> samples={};

public:

	ADC_Service(Dispatcher *disp);
	Dispatcher *disp;
	thread* ADCInterruptServiceThread;
	vector<int8_t> events;

	int dispId;
	virtual ~ADC_Service();
	void adcInterruptService();
	WSAData *wsa_data;

	void startSMZHoehenCheck();
	int setWS_hoehe();
	int getGemssenehoehe(int type);
};

#endif /* SRC_MAIN_HAL_ADC_SERVICE_H_ */
