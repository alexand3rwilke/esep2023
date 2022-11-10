/*
 * Sensor.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_Sensor_H_
#define SRC_MAIN_HAL_Sensor_H_


class Sensor  {

public:
	Sensor();
	virtual ~Sensor();

	int getValueAtPin(void);
};

#endif /* SRC_MAIN_HAL_Sensor_H_ */
