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
#include "../Imports.h"
#include "TimerBZ.h"
#include "Werkstueck.h"

class Context {
private:
	//Basestate *state;
	Basestate *fisrsState;
	std::thread* ContextThread;
	std::vector<int8_t> events;
	std::vector<int> werkstuckReihenfolgeList;
	void eventHandler();
	int dispID;

public:
	Context(Dispatcher *dispatcher, Actions *actions, ContextData  * contextData, vector<int> werkstuckReihenfolge);


	TimerBZ *timerBz;
	virtual ~Context();
	void entry();
	void exit();
	void estp();
	void doAction();
	ContextData *contextData;
	Dispatcher *disp;
	Actions *actions;

private:
	void setWkInStateWhereNotSet(WkType wkType);
	int wkReihenfolgeIndex;
	int stateIndex;
	bool firstState = true; // wird direkt beim ersten LSA trigger auf false gesetzt
};

#endif /* SRC_MAIN_LOGIC_CONTEXT_H_ */
