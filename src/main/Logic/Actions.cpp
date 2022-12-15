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

void Actions::switchOn(int conID){
	MsgSendPulse(conID,-1,ACTIVTE_AUSSORTIERER,0);
}

void Actions::startFB(int conID){

	MsgSendPulse(conID,-1,START_FB,0);

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

// muss noch eingebaut werden
void Actions::durchlassen(int conID){
	MsgSendPulse(conID,-1,WS_DURCHLASSEN,0);
}
void Actions::aussortieren(int conID){
	MsgSendPulse(conID,-1,WS_AUSSORTIEREN,0);
}

/*------------------------Ampel--------------------------*/

void Actions::greenOn(int conID){
	printf("Actions green on los-------- \n");
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

void Actions::greenLightBlinking(int coID){
	//MsgSendPulse(conID,-1,xxx,0);
}
void Actions::greenLightBlinkingOff(int coID){
	//MsgSendPulse(conID,-1,xxx,0);
}
/*----------------LED---------------------*/

void Actions::ledQ1On(int coID){
	MsgSendPulse(coID,-1,Q1On,0);
}

void Actions::ledQ2On(int coID){
	MsgSendPulse(coID,-1,Q2On,0);
}

void Actions::ledQ1Off(int coID){
	MsgSendPulse(coID,-1,Q1On,0);
}

void Actions::ledQ2Off(int coID){
	MsgSendPulse(coID,-1,Q2Off,0);
}

