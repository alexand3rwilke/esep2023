
/*
 * ISR.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_ISR_H_
#define SRC_MAIN_HAL_ISR_H_


#include <thread>





class ISR  {

public:
	ISR();
	virtual ~ISR();
	void handleInterrupt(void);
	void recieveInterruptRoutine();


	std::thread* ISRRoutineThread;
};

#endif /* SRC_MAIN_HAL_ISR_H_ */
