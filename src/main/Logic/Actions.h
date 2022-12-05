/*
 * Actions.h
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_ACTIONS_H_
#define SRC_MAIN_LOGIC_ACTIONS_H_

#include "Imports.h"




class Actions {
private:
	int coID;
public:
	Actions(int coId);
	virtual ~Actions();
	void startFB();
	void stopFB();
	void moveFaster();
	void moveSlower();
	void greenOn();
	void greenOff();
	void yellowOn();
	void yellowOff();
	void redOn();
	void redOff();



};

#endif /* SRC_MAIN_LOGIC_ACTIONS_H_ */
