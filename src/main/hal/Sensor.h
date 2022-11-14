
/*
 * Sensor.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_Sensor_H_
#define SRC_MAIN_HAL_Sensor_H_

#include "../Imports.h"
#include "stdint.h"



class Sensor  {

public:
	Sensor();
	virtual ~Sensor();

	int getValueAtPin(int pin);
};

#endif /* SRC_MAIN_HAL_Sensor_H_ */
