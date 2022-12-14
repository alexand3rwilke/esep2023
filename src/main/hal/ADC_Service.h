
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

class ADC_Service  {

public:

	ADC_Service(Dispatcher *disp);
	Dispatcher *disp;
	std::thread* ADCServiceThread;
	std::vector<int8_t> events;
	int dispId;
	virtual ~ADC_Service();
	void adcService();

};

#endif /* SRC_MAIN_HAL_ADC_SERVICE_H_ */
