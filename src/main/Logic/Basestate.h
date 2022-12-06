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

	virtual void entry() {};
	virtual void exit() {};
	virtual void estp() {};
	virtual void doAction() {};

	//
};



#endif /* SRC_MAIN_LOGIC_BASESTATE_H_ */
