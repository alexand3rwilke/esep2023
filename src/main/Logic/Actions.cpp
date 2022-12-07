/*
 * Actions.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#include "../dispatcher/Dispatcher.h"
#include "Actions.h"

Actions::Actions(
		//Dispatcher *dispatcher
		) {
	//disp = dispatcher;
	//coID = dispatcher->getConnectionID();
	}

Actions::~Actions() {
	//delete coID;
}

void Actions::setConId(int conId){

	coID = conId;
}
void Actions::startFB(int conId){
	MsgSendPulse(coID,-1,START_FB,0);
}

void Actions::stopFB(int coID){
	MsgSendPulse(coID,-1,STOP_FB,0);

}

void Actions::moveFaster(int coID){
	MsgSendPulse(coID,-1,MOVE_FASTER,0);
}

void Actions::moveSlower(int coID){
	MsgSendPulse(coID,-1,MOVE_SLOWER,0);
}

void Actions::greenOn(int coID){
	MsgSendPulse(coID,-1,GREEN_ON,0);
}

void Actions::greenOff(int coID){
	MsgSendPulse(coID,-1,GREEN_OFF,0);
}

void Actions::yellowOn(int coID){
	MsgSendPulse(coID,-1,YELLOW_ON,0);
}

void Actions::yellowOff(int coID){
	MsgSendPulse(coID,-1,YELLOW_OFF,0);
}

void Actions::redOn(int coID){
	MsgSendPulse(coID,-1,RED_ON,0);
}

void Actions::redOff(int coID){
	MsgSendPulse(coID,-1,RED_OFF,0);
}






