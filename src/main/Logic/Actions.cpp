/*
 * Actions.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#include "Actions.h"

Actions::Actions(Dispatcher *dispatcher) {
	disp = dispatcher;
	coID = dispatcher->getConnectionID();
}

Actions::~Actions() {
	//delete coID;
}




void Actions::startFB(){
	MsgSendPulse(coID,-1,START_FB,0);
}

void Actions::stopFB(){
	MsgSendPulse(coID,-1,STOP_FB,0);

}

void Actions::moveFaster(){
	MsgSendPulse(coID,-1,MOVE_FASTER,0);
}

void Actions::moveSlower(){
	MsgSendPulse(coID,-1,MOVE_SLOWER,0);
}

void Actions::greenOn(){
	MsgSendPulse(coID,-1,GREEN_ON,0);
}

void Actions::greenOff(){
	MsgSendPulse(coID,-1,GREEN_OFF,0);
}

void Actions::yellowOn(){
	MsgSendPulse(coID,-1,YELLOW_ON,0);
}

void Actions::yellowOff(){
	MsgSendPulse(coID,-1,YELLOW_OFF,0);
}

void Actions::redOn(){
	MsgSendPulse(coID,-1,RED_ON,0);
}

void Actions::redOff(){
	MsgSendPulse(coID,-1,RED_OFF,0);
}






