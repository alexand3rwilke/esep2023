/*
 * TimerBZ.h
 *
 *  Created on: 21.12.2022
 *      Author: Jobut
 */
#include "../Imports.h"
#include "Context.h"

#ifndef SRC_MAIN_LOGIC_TIMERBZ_H_
#define SRC_MAIN_LOGIC_TIMERBZ_H_

class TimerBZ {
private:

	time_t start_time;
	time_t end_time;

	double timerResult;

public:
	TimerBZ();
	virtual ~TimerBZ();

	void startTimer();
//	double stopTimer();
	void stopTimer();



};

#endif /* SRC_MAIN_LOGIC_TIMERBZ_H_ */
