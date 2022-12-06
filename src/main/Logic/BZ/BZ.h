/*
 * BZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#ifndef SRC_MAIN_LOGIC_BZ_BZ_H_
#define SRC_MAIN_LOGIC_BZ_BZ_H_

#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"

using namespace std;

/**
 * Erbt von Basic_State
 */
class BZ : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;

public:
	void entry()override;
};

#endif /* SRC_MAIN_LOGIC_BZ_H_ */
