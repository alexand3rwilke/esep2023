
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
	void printSamples();

public:

	ADC_Service(Dispatcher *disp);
	Dispatcher *disp;
	thread* ADCInterruptServiceThread;
	vector<int8_t> events;
	vector<int> samples;
	int dispId;
	virtual ~ADC_Service();
	void adcInterruptService();
	WSAData *wsa_data;


};

#endif /* SRC_MAIN_HAL_ADC_SERVICE_H_ */
