/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */


#include "BZAuslauf.h"



void BZAuslauf::entry() {


	doAction();

}
    void BZAuslauf::exit() {

    }
    void BZAuslauf::estp() {


    }
    void BZAuslauf::doAction(){

    	_pulse msg;
    	int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);

    	if (recvid < 0) {
    				perror("MsgReceivePulse failed!");
    			}

    			if (recvid == 0) {
    			while(true) {

    		switch (msg.code) {


    		// wenn fertig dann in Auslauf
    		case 12 :
    					entry();
    					break;





    		}


    		}
    			}

    	}
