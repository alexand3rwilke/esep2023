/*
 * Actions.h
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_ACTIONS_H_
#define SRC_MAIN_LOGIC_ACTIONS_H_

#include "../Imports.h"
#include "../dispatcher/Dispatcher.h"

class Actions {
private:
	Dispatcher *disp;
	int conID;

public:
	Actions(Dispatcher *disp);
	virtual ~Actions();

	//Aktorik
	//void setConId(void);
	void startFB(void);
	void stopFB(void);
	void moveFaster(void);
	void moveSlower(void);

	void durchlassen(void);
	void aussortieren(void);


	//Ampel
	void greenOn(void);
	void greenOff(void);
	void yellowOn(void);
	void yellowOff(void);
	void redOn(void);
	void redOff(void);
	void ampAllOff(void);

	void greenLightBlinking(void);
	void yellowLightBlinking(void);
	void redLightBlinkingFast(void);
	void redLightBlinkingSlow(void);

	//LED
	void ledQ1On(void);
	void ledQ2On(void);
	void ledQ1Off(void);
	void ledQ2Off(void);


};

#endif /* SRC_MAIN_LOGIC_ACTIONS_H_ */
