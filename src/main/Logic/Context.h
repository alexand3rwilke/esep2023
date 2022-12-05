/*
 * Context.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_CONTEXT_H_
#define SRC_MAIN_LOGIC_CONTEXT_H_
#include "BaseState.h"

class Context {
private:
	BaseState *state;

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
