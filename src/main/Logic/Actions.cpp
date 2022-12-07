/*
 * Actions.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#include "../dispatcher/Dispatcher.h"
#include "Actions.h"

Actions::Actions() {
//	disp = dispatcher;
//	conID = disp->getConnectionID();
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

void Actions::stopFB(int conID){
	MsgSendPulse(conID,-1,STOP_FB,0);

}

void Actions::moveFaster(int conID){
	MsgSendPulse(conID,-1,MOVE_FASTER,0);
}

void Actions::moveSlower(int conID){
	MsgSendPulse(conID,-1,MOVE_SLOWER,0);
}

void Actions::greenOn(int conID){
	MsgSendPulse(conID,-1,GREEN_ON,0);
}

void Actions::greenOff(int conID){
	MsgSendPulse(conID,-1,GREEN_OFF,0);
}

void Actions::yellowOn(int conID){
	MsgSendPulse(conID,-1,YELLOW_ON,0);
}

void Actions::yellowOff(int conID){
	MsgSendPulse(conID,-1,YELLOW_OFF,0);
}

void Actions::redOn(int conID){
	MsgSendPulse(conID,-1,RED_ON,0);
}

void Actions::redOff(int conID){
	MsgSendPulse(conID,-1,RED_OFF,0);
}






