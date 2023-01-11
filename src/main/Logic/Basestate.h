/*
 * Basestate.h
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_BASESTATE_H_
#define SRC_MAIN_LOGIC_BASESTATE_H_


#include "Actions.h"
#include "ContextData.h"
#include "../WSAData.h"


class Basestate {
protected:
	//Befehle der HAL

	Basestate *substate;

	Actions *actions;
	WSAData *wsa_data;
	ContextData *contextData;
	int myChannel;
	int myConnection;

	int dispId;



public:

	virtual ~Basestate(){
	};

	virtual void entry() {};
	virtual void exit() {};
	virtual void estp() {};
	virtual void doAction(int, _pulse) {};

	void setActions(Actions *actions) {this->actions = actions;};
	void setContextData(ContextData *contextData) {this->contextData = contextData;};
	void setDispId(int dispId) {this->dispId = dispId;};

	//
};



#endif /* SRC_MAIN_LOGIC_BASESTATE_H_ */
