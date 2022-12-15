/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"

#include "../ESZ/ESZ.h"
#include "../ESZ/ESZ.h"


void BZ::entry(){
	// grünes licht an entry
	actions->greenOn(1);
	substate = NULL;
}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff(1);
}

void BZ::doAction (int event) {



	_pulse msg;
		while(true){
			int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);

			if (recvid < 0) {
				perror("MsgReceivePulse failed!");
			}

			if (recvid == 0) {

				switch (msg.code) {

				// TODO  change case
				case SRT :	new(this) BZ;
							entry();
							break;

				case ESTP:	new(this) ESZ;
						entry();
						break;
				}
			}
		}
}
