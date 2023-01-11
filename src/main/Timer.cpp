/*
 * Timer.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "Timer.h"

using namespace std;

Timer::Timer(Dispatcher *disp, int conID ) {
	this->dispatcher = disp;
	this->conID = conID;
	timerThread = new thread([this]() {running();});
}

Timer::~Timer() {
}

int Timer::running(){
	while(true){
		this_thread::sleep_for(chrono::milliseconds(40));
		MsgSendPulse(conID, -1,TimerTimeout,0);
	}
	return 1;
}
