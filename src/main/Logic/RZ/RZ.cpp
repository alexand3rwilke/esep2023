/*
 * RZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "RZ.h"



void RZ::entry() {

	actions->greenOn(contextData->disp->getConnectionID());
	actions->yellowOff(contextData->disp->getConnectionID());
	actions->redOff(contextData->disp->getConnectionID());
	printf("---in rz entry");
	doAction();


}
    void RZ::exit() {

    }
    void RZ::estp() {


    }
    void RZ::doAction(){

//    	_pulse msg;
//
//    	int chanID = ChannelCreate(0);
//    	int ConID = ConnectAttach(0,0,chanID,_NTO_SIDE_CHANNEL,0);
//
//    	int recvid = MsgReceivePulse(contextData->disp->getConnectionID(), &msg, sizeof(_pulse), nullptr);
//
//    	if (recvid < 0) {
//    				perror("MsgReceivePulse failed in RZ State!");
//    			}
//
//    			if (recvid == 0) {
//    			while(true) {

    		switch (msg.code) {

    		case 12 : new(this) BZ; entry(); break;





    		}


    		}
    			}

    	}



