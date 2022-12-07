/*
 * RZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "RZ.h"



void RZ::entry() {







	actions->greenOff(data->conIDDis);
	actions->yellowOff(data->conIDDis);
	actions->redOff(data->conIDDis);
	doAction();

}
    void RZ::exit() {

    }
    void RZ::estp() {


    }
    void RZ::doAction(){

    	_pulse msg;
    	int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);

    	if (recvid < 0) {
    				perror("MsgReceivePulse failed!");
    			}

    			if (recvid == 0) {
    			while(true) {

    		switch (msg.code) {

    		case 12 : new(this) BZ; entry(); break;





    		}


    		}
    			}

    	}



