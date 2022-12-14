/*
 * Actuator.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
 */


#ifndef SRC_MAIN_HAL_ACTUATOR_H_
#define SRC_MAIN_HAL_ACTUATOR_H_


#include "../Imports.h"
#include "../Dispatcher/Dispatcher.h"

class Actuator  {
private:
	Dispatcher *disp;

public:
	Actuator(Dispatcher *dispatcher);
	virtual ~Actuator();

	_pulse pulse;

	vector<int8_t> actuatorEvents;
	void handleEvents(void);
	thread* aktuatorThread;


	void assamblyMoveRightOn(void);
	void assamblyMoveRightOff(void);
	void assamblyMoveLeftOn(void);
	void assamblyMoveLeftOff(void);
	void assamblyMoveSlowOn(void);
	void assamblyMoveSlowOff(void);
	void assamblyStopOn(void);
	void assamblyStopOff(void);
	void redOn(void);
	void redOff(void);
	void yellowOn(void);
	void yellowOff(void);
	void greenOn(void);
	void greenOff(void);
	void switchOn(void);
	void switchOff(void);
};

#endif /* SRC_MAIN_HAL_ACTUATOR_H_ */
