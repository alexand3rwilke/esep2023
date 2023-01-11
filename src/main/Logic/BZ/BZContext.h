/*
 * BZContext.h
 *
 *  Created on: 23.12.2022
 *      Author: Jobut
 */



#ifndef SRC_MAIN_LOGIC_BZ_BZCONTEXT_H_
#define SRC_MAIN_LOGIC_BZ_BZCONTEXT_H_

#include "../Context.h"
#include "../ContextData.h"
#include "../Basestate.h"

#include "../RZ/RZ.h"
#include "BZ.h"
#include "../ESZ/ESz.h"
#include "../SMZ/SMZ.h"
#include "../FZ/AnstehendQuittiert.h"

#include <stdio.h>
#include <iostream>


class BZContext {
private:
	Basestate *state;
	std::thread* BZContextThread;
	std::thread* bzThread;
	std::vector<int8_t> events;
	std::vector<thread> stateThreadsBZ;

	void eventHandler();
public:
	BZContext();
	virtual ~BZContext();;
	ContextData *contextData;
	Dispatcher *disp;
	Actions *actions;
};


#endif /* SRC_MAIN_LOGIC_BZ_BZCONTEXT_H_ */
