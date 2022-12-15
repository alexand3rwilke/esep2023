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
#include "Amp.h"

class Actuator  {
private:
	Dispatcher *disp;
	Amp *amp;

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

	void switchOn(void);
	void switchOff(void);
	void ampOff(void);


	void start_LedOn(void);

	void start_LedOff(void);
	void stop_LedOn(void);

	void stop_LedOff(void);

	void q1_LedOn(void);

	void q1_LedOff(void);

	void q2_LedOn(void);

	void q2_LedOff(void);


	int getAussortierer(void);

	uintptr_t gpio_bank_0;
	uintptr_t gpio_bank_1;
	uintptr_t gpio_bank_2;


};

#endif /* SRC_MAIN_HAL_ACTUATOR_H_ */
