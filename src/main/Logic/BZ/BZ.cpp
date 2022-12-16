/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"
#include "../RZ/RZ.h"

void BZ::entry(){
	// grünes licht an entry
	actions->greenOn();

	substate = NULL;


}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff();
	actions->stopFB();
}


void BZ::doAction (int event) {




//	_pulse msg;
//		while(true){
//			int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);
//
//			if (recvid < 0) {
//				perror("MsgReceivePulse failed!");
//			}



				switch (event) {


			   case LSAinterrupted:
				   actions->startFB();
				   break;

			   case LSSinterrupted:
				   actions->durchlassen();
				   break;

			   case LSEinterrupted:
				   actions->stopFB();
				   break;

			   case STPinterrupted:
			  		exit();
			  		new (this) RZ;
			  		entry();
			  		break;


				case ESTP:	new(this) ESZ;
						entry();
						break;
				}

}

