/*
 * Timer.h
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_TIMER_H_
#define SRC_MAIN_TIMER_H_

#include "Dispatcher/Dispatcher.h"
#include "Imports.h"

class Timer {
private:
	time_t startTime;
	time_t endTime;
	double timeDiff;
	int myChannel;
	int myConnection;
	int conID;
	Dispatcher *dispatcher;

public:
	Timer(Dispatcher *disp, int conID);
	virtual ~Timer();
	thread *timerThread;
	int running();
};
#endif /* SRC_MAIN_TIMER_H_ */

