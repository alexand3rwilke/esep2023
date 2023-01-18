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
//#include "TimerBZ.h"
#include "SimpleTimer.h"


class Basestate {
protected:
	//Befehle der HAL

	//TimerBZ *timerBz;
	SimpleTimer *stateTimer;
	Basestate *substate;

	vector<Basestate *> substateList;
	Actions *actions;
	WSAData *wsa_data;
	ContextData *contextData;
	int myChannel;
	int myConnection;


	int dispId;
	int stateId;

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
	//void setErkanntesWK(int wkType) {contextData->setErkanntesWk(wkType);};
	//void setZielWK(int wkType) {contextData->setZielWk(wkType);};
	void setStateId(int stateId) {this->stateId= stateId;};

	//int getErkanntesWK(int dispId) {return contextData->getErkanntesWk();};
	//int getZielWK(int dispId) {return contextData->getZielWk();};
	int getStateId() {return stateId;};

	//
};



#endif /* SRC_MAIN_LOGIC_BASESTATE_H_ */
