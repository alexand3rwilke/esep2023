/*
 * Context.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_CONTEXT_H_
#define SRC_MAIN_LOGIC_CONTEXT_H_
#include "BasicState.h"

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
};

#endif /* SRC_MAIN_LOGIC_CONTEXT_H_ */
