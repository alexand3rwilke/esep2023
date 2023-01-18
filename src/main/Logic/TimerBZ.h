/*
 * TimerBZ.h
 *
 *  Created on: 21.12.2022
 *      Author: Jobut
 */
#include "../Imports.h"
#include "Context.h"
#include "../dispatcher/Dispatcher.h"

#ifndef SRC_MAIN_LOGIC_TIMERBZ_H_
#define SRC_MAIN_LOGIC_TIMERBZ_H_

class TimerBZ {
private:
	Dispatcher *disp;
	int dispConID;
	time_t start_time;
	time_t end_time;
	double seconds;
	std::thread* timer;
	std::thread* chanKeeper;
	bool recivedIntereupt = false;
	double timerResult;
	int event;
	int reactionEvent;

	void setUp();
	void timerGestartet();

public:
	TimerBZ();
	TimerBZ(Dispatcher *disp,int seconds, int event, int reactionEvent);
	virtual ~TimerBZ();
	void startTimer();
//	double stopTimer();
	void stopTimer();



};

#endif /* SRC_MAIN_LOGIC_TIMERBZ_H_ */
