/*
 * Actions.h
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_ACTIONS_H_
#define SRC_MAIN_LOGIC_ACTIONS_H_

#include "../Imports.h"
#include <sys/neutrino.h>
#include "../dispatcher/Dispatcher.h"



//#include <iostream>
//#include <stdint.h>
//#include <sys/mman.h>
//#include <hw/inout.h>


//#include <errno.h>
//#include <sys/procmgr.h>//
//#include <iostream>
//#include <thread>
//#include <chrono>




class Actions {
private:

	int coID;
	//Dispatcher *disp = NULL;

public:
	Actions();
	virtual ~Actions();

	void setConId(int conId);
	void startFB(int coID);
	void stopFB(int coID);
	void moveFaster(int coID);
	void moveSlower(int coID);
	void greenOn(int coID);
	void greenOff(int coID);
	void yellowOn(int coID);
	void yellowOff(int coID);
	void redOn(int coID);
	void redOff(int coID);
	void switchOn(int coID);
	void greenLightBlinking(int coID);
	void greenLightBlinkingOff(int coID);
};

#endif /* SRC_MAIN_LOGIC_ACTIONS_H_ */
