/*
 * TimerBZ.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Jobut
 */

#include "TimerBZ.h"


TimerBZ::TimerBZ() {
	// TODO Auto-generated constructor stub

}

TimerBZ::~TimerBZ() {
	// TODO Auto-generated destructor stub
}

void TimerBZ::startTimer(){

	start_time = time(NULL);
}

void TimerBZ::stopTimer(){

	end_time = time(NULL);
	double timerResult = difftime(end_time,start_time);
	cout << timerResult << endl;

}

