/*
 * Basestate.h
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_BASESTATE_H_
#define SRC_MAIN_LOGIC_BASESTATE_H_

#include "Actions.h"

class Basestate {
private:
	//Befehle der HAL
	Actions *actions;


	int myChannel;
	int myConnection;

public:
	virtual ~Basestate(){
	};
	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void estp() = 0;
	virtual void doAction() = 0;
	//
};



#endif /* SRC_MAIN_LOGIC_BASESTATE_H_ */
