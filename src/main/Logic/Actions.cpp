/*
 * Actions.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Jobut
 */

#include "../dispatcher/Dispatcher.h"
#include "Actions.h"

Actions::Actions(Dispatcher *dispatcher) {
	disp = dispatcher;
	conID = disp->getConnectionID();
	}

Actions::~Actions() {
	//delete coID;
}

/*------------------Aktorik----------------------*/

void Actions::switchOn(){
	MsgSendPulse(conID,-1,ACTIVTE_AUSSORTIERER,0);
}

void Actions::startFB(){

	MsgSendPulse(conID,-1,START_FB,0);

}

void Actions::stopFB(){
	MsgSendPulse(conID,-1,STOP_FB,0);

}

void Actions::moveFaster(){
	MsgSendPulse(conID,-1,MOVE_FASTER,0);
}

void Actions::moveSlower(){
	MsgSendPulse(conID,-1,MOVE_SLOWER,0);
}

// muss noch eingebaut werden
void Actions::durchlassen(){
	MsgSendPulse(conID,-1,WS_DURCHLASSEN,0);
}
void Actions::aussortieren(){
	MsgSendPulse(conID,-1,WS_AUSSORTIEREN,0);
}

/*------------------------Ampel--------------------------*/

void Actions::greenOn(){
	printf("Actions green on los-------- \n");
	MsgSendPulse(conID,-1,GREEN_ON,0);
}

void Actions::greenOff(){
	MsgSendPulse(conID,-1,GREEN_OFF,0);
}

void Actions::yellowOn(){
	MsgSendPulse(conID,-1,YELLOW_ON,0);
}

void Actions::yellowOff(){
	MsgSendPulse(conID,-1,YELLOW_OFF,0);
}

void Actions::redOn(){
	MsgSendPulse(conID,-1,RED_ON,0);
}

void Actions::redOff(){
	MsgSendPulse(conID,-1,RED_OFF,0);
}

void Actions::greenLightBlinking(){
	//MsgSendPulse(conID,-1,xxx,0);
}
void Actions::greenLightBlinkingOff(){
	//MsgSendPulse(conID,-1,xxx,0);
}
/*----------------LED---------------------*/

void Actions::ledQ1On(){
	MsgSendPulse(conID,-1,Q1On,0);
}

void Actions::ledQ2On(){
	MsgSendPulse(conID,-1,Q2On,0);
}

void Actions::ledQ1Off(){
	MsgSendPulse(conID,-1,Q1On,0);
}

void Actions::ledQ2Off(){
	MsgSendPulse(conID,-1,Q2Off,0);
}

