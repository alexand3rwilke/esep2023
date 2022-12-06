/*
 * Context.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#ifndef SRC_MAIN_LOGIC_CONTEXT_H_
#define SRC_MAIN_LOGIC_CONTEXT_H_

#include "../dispatcher/Dispatcher.h"
#include "Basestate.h"
#include "Actions.h"


class Context {
private:
	Basestate *state;
	std::thread* ContextThread = NULL;
	std::vector<int8_t> events;
	void eventHandler();

public:
	Context(Dispatcher *dispatcher, Actions *actions);
	virtual ~Context();
	void entry();
	void exit();
	void estp();
	void doAction();

	Dispatcher *disp = NULL;
	Actions *actions = NULL;
};

#endif /* SRC_MAIN_LOGIC_CONTEXT_H_ */
