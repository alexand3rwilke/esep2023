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
class Context {
private:
	//Basestate *state;
	vector<Basestate *> stateList;
	std::thread* ContextThread;
	std::vector<int8_t> events;
	std::vector<int> werkstuckReihenfolgeList;
	void eventHandler();
	int dispID;
	void setWkInStateWhereNotSet(int wkType);
	int wkReihenfolgeIndex;
	int stateIndex;
	bool firstState = true; // wird direkt beim ersten LSA trigger auf false gesetzt

public:
	Context(Dispatcher *dispatcher, Actions *actions, ContextData  * contextData, vector<int> werkstuckReihenfolge);

	virtual ~Context();
	TimerBZ *timerBz;
	void entry();
	void exit();
	void estp();
	void doAction();
	ContextData *contextData;
	Dispatcher *disp;
	Actions *actions;


};

#endif /* SRC_MAIN_LOGIC_CONTEXT_H_ */
