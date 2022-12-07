/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZready.h"
#include "BZEinlauf.h"


void BZready::entry() {


	doAction();

}
    void BZready::exit() {

    }
    void BZready::estp() {


    }
    void BZready::doAction(){

    	_pulse msg;
    	int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);

    	if (recvid < 0) {
    				perror("MsgReceivePulse failed!");
    			}

    			if (recvid == 0) {
    			while(true) {

    		switch (msg.code) {


    		// check ob LSE interrupt bekommt
    		case LSE1 :	new(this) BZEinlauf;
    					entry();
    					break;





    		}


    		}
    			}

    	}
