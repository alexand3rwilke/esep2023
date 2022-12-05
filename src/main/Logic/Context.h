/*
 * Context.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_CONTEXT_H_
#define SRC_MAIN_LOGIC_CONTEXT_H_

#include "BaseState.h"
#include "Actions.h"
//#include "Dispatcher.h"
#include "../dispatcher/Dispatcher.h"

#include <sys/neutrino.h>

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>


#include <errno.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <list>

#include <hw/inout.h>
#include <sys/neutrino.h>


class Context {
private:
	BaseState *state;
	Actions *actions;
	void eventHandler();
	std::thread* ContextThread;
	std::vector<int8_t> events;
	Dispatcher *disp;

public:
	Context(Dispatcher *dispatcher, Actions *actions);
	virtual ~Context();
	void entry();
	void exit();
	void estp();
	void doAction();

	//Dispatcher *disp = NULL;
};

#endif /* SRC_MAIN_LOGIC_CONTEXT_H_ */
