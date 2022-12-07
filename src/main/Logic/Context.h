/*
 * Context.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#ifndef SRC_MAIN_LOGIC_CONTEXT_H_
#define SRC_MAIN_LOGIC_CONTEXT_H_

#include "../dispatcher/Dispatcher.h"
#include "Actions.h"
#include "Basestate.h"
#include "ContextData.h"




class Context {
private:
	Basestate *state;

	std::thread* ContextThread;
	std::vector<int8_t>* events;
	void eventHandler();

public:
	Context(Dispatcher *dispatcher, Actions *actions, ContextData  * contextData);

	virtual ~Context();
	void entry();
	void exit();
	void estp();
	void doAction();
	ContextData *contextData;
	Dispatcher *disp;
	Actions *actions;
};

#endif /* SRC_MAIN_LOGIC_CONTEXT_H_ */
