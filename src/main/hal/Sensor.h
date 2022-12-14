
/*
 * Sensor.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_Sensor_H_
#define SRC_MAIN_HAL_Sensor_H_

#include "../Imports.h"
#include "../Dispatcher/Dispatcher.h"


class Sensor  {
private:
	vector<int8_t> senorEvents;

public:
	std::thread* SensorRoutineThread;
	Dispatcher *disp;
	int dispID;
	Sensor(Dispatcher * dispatcher);
	virtual ~Sensor();
	void sensorRoutine();

};

#endif /* SRC_MAIN_HAL_Sensor_H_ */
