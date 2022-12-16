/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"

void BZ::entry(){
	// grünes licht an entry
	actions->greenOn();
	substate = NULL;
	sleep(5);
	exit();
}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff();
}

void BZ::doAction (int event) {
}

