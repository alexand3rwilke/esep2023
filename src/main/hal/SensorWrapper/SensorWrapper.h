/*
 * SensorWrapper.h
 *
 *  Created on: 6 Jan 2023
 *      Author: Alexander Wilke
 */

#ifndef SRC_HAL_SENSORWRAPPER_SENSORWRAPPER_H_
#define SRC_HAL_SENSORWRAPPER_SENSORWRAPPER_H_

#include <iostream>
#include <stdint.h>



class SensorWrapper {
public:
	SensorWrapper();
	virtual ~SensorWrapper();
	static int readPin(uint32_t bank, uint32_t bit);

};

#endif /* SRC_HAL_SENSORWRAPPER_SENSORWRAPPER_H_ */
