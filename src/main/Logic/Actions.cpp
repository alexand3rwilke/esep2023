/*
 * Actions.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#include "Actions.h"

Actions::Actions(int dispID) {
	coID = dispID
}

Actions::~Actions() {
	delete coID;
}




Actions::startFB(){
	MsgSendPulse(coID,-1,START_FB,0);
}

Actions::stopFB(){
	MsgSendPulse(coID,-1,STOP_FB,0);

}

Actions::moveFaster(){
	MsgSendPulse(coID,-1,MOVE_FASTER,0);
}

Actions::moveSlower(){
	MsgSendPulse(coID,-1,MOVE_SLOWER,0);
}

Actions::greenOn(){
	MsgSendPulse(coID,-1,GREEN_ON,0);
}

Actions::greenOff(){
	MsgSendPulse(coID,-1,GREEN_OFF,0);
}

Actions::yellowOn(){
	MsgSendPulse(coID,-1,YELLOW_ON,0);
}

Actions::yellowOff(){
	MsgSendPulse(coID,-1,YELLOW_OFF,0);
}

Actions::redOn(){
	MsgSendPulse(coID,-1,RED_ON,0);
}

Actions::redOff(){
	MsgSendPulse(coID,-1,RED_OFF,0);
}




