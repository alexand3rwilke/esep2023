/*
 * Amp.h
 *
 *  Created on: 15.12.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_HAL_AMP_H_
#define SRC_MAIN_HAL_AMP_H_

//#include "Actuator.h"
#include "../Imports.h"
using namespace std;

enum TrafficColer {
    GREEN, YELLOW, RED,
};

class Amp {
private:

	uintptr_t gpio_bank_1;


	std::thread* red_thread;
	std::thread* yellow_thread;
	std::thread* green_thread;
	bool redIsFlashing;
	bool yellowIsFlashing;
	bool greenIsFlashing;

	void redFlashing(int);
	void yellowFlashing(int);
	void greenFlashing(int);
public:
	Amp();
	virtual ~Amp();
	void ampOff(void);

	void redOn(void);
	void redOff(void);
	void yellowOn(void);
	void yellowOff(void);
	void greenOn(void);
	void greenOff(void);
	void greenBlinken(int);


	 void flashinLight(TrafficColer, int);
};


#endif /* SRC_MAIN_HAL_AMP_H_ */
