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
	void setConId(int conId);
	void startFB(int coID);
	void stopFB(int coID);
	void moveFaster(int coID);
	void moveSlower(int coID);
	void switchOn(int coID);

	void durchlassen(int conID);
	void aussortieren(int conID);//doppelt ? wegen switch on ?

	//Ampel
	void greenOn(int coID);
	void greenOff(int coID);
	void yellowOn(int coID);
	void yellowOff(int coID);
	void redOn(int coID);
	void redOff(int coID);

	void greenLightBlinking(int coID);
	void greenLightBlinkingOff(int coID);

	//LED
	void ledQ1On(int coID);
	void ledQ2On(int coID);
	void ledQ1Off(int coID);
	void ledQ2Off(int coID);
};

#endif /* SRC_MAIN_LOGIC_ACTIONS_H_ */
