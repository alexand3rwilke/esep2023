/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"

void BZ::entry(){
	// grünes licht an entry
	int x = wsa_data->dispID;
	actions->greenOn(wsa_data->dispID);
	substate = NULL;
	sleep(1);
	exit();
}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff(wsa_data->dispID);
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
				case STR :	new(this) BZ;
							entry();
							break;

				case ESTP:	new(this) ESZ;
						entry();
						break;
				}
			}
		}
}

