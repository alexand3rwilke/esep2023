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
public:
	Actions(int coId);
	virtual ~Actions();

	void startFB();
	void stopFB(void);
	void moveFaster(void);
	void moveSlower(void);
	void greenOn(void);
	void greenOff(void);
	void yellowOn(void);
	void yellowOff(void);
	void redOn(void);
	void redOff(void);



};

#endif /* SRC_MAIN_LOGIC_ACTIONS_H_ */
