/*
 * SMZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "SMZ.h"

void SMZ :: entry(){
	actions->greenLightBlinking(1);
	substate = NULL;
	doAction();
}

void SMZ :: exit(){
	actions->greenLightBlinkingOff(1);
}

void SMZ :: doAction(){

	_pulse pulseMsg;
			while(true){
				int recvid = MsgReceivePulse(myChannel, &pulseMsg, sizeof(_pulse), nullptr);

				if (recvid < 0) {
					perror("MsgReceivePulse failed!");
				}

				if (recvid == 0) {

					switch (pulseMsg.code) {
					//Choose calibrationmode
					case SRT:	new(this)SMZCalibration;
								entry();
								break;

					//Choose testmode
					case STP:	new(this)SMZTesting;
								entry();
								break;
					}
				}
			}
}
