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
#include "../Dispatcher/Dispatcher.h"


class Sensor  {

public:
	Sensor(Dispatcher * dispatcher);
	virtual ~Sensor();

<<<<<<< HEAD
	int getValueAtPin(int);
=======
	int getValueAtPin(int pin);
>>>>>>> aa97bcff3895cee9b7e7d7fd0c7c218067f53c71
};

#endif /* SRC_MAIN_HAL_Sensor_H_ */

