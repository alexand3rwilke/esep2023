
/*
 * ISR.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_ISR_H_
#define SRC_MAIN_HAL_ISR_H_

#include "../Imports.h"
#include "../Dispatcher/Dispatcher.h"
#include <thread>
#include "../hal/Sensor.h"





class ISR  {

public:
	ISR(Dispatcher *dispatcher);
	//ISR(Sensor *sensor);
	Dispatcher disp;
	int dispId;
	virtual ~ISR();
	void handleInterrupt(void);
	void recieveInterruptRoutine();


	std::thread* ISRRoutineThread;
};

#endif /* SRC_MAIN_HAL_ISR_H_ */
