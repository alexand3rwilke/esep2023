
/*
 * ADC.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_ADC_H_
#define SRC_MAIN_HAL_ADC_H_

#include "Addresses.h"
#include "stdint.h"



class ADC  {

public:
	ADC();
	virtual ~ADC();
	uint32_t readHeight();
};

#endif /* SRC_MAIN_HAL_ADC_H_ */
