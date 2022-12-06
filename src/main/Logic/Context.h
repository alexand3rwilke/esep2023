/*
 * Context.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#ifndef SRC_MAIN_LOGIC_CONTEXT_H_
#define SRC_MAIN_LOGIC_CONTEXT_H_

#include "BasicState.h"
#include "../dispatcher/Dispatcher.h"

class Context {
private:
	BasicState *state;

public:
	Context();
	virtual ~Context();
	void entry();
	void exit();
	void estp();
	void doAction();

	Dispatcher *dispa = NULL;
};

#endif /* SRC_MAIN_LOGIC_CONTEXT_H_ */
