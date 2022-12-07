/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"

void BZ::entry(){
	// grünes licht an entry
	actions->greenOn(1);
	doAction();
}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff(1);
}

void BZ::doAction () {



	_pulse msg;
		while(true){
			int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);

			if (recvid < 0) {
				perror("MsgReceivePulse failed!");
			}

			if (recvid == 0) {

				switch (msg.code) {

				case 1 : new(this) BZ;
				}
			}
		}
}
