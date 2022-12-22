/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */


#include "BZAuslauf.h"
#include "BZready.h"



void BZAuslauf::entry() {

	cout << "\n  BZAuslauf entry\n" << endl;
	actions->stopFB();

}
    void BZAuslauf::exit() {

    }
    void BZAuslauf::estp() {


    }
    void BZAuslauf::doAction(int event, _pulse){

    	_pulse msg;
    	int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);

    	if (recvid < 0) {
    				perror("MsgReceivePulse failed!");
    			}

    			if (recvid == 0) {
    			while(true) {

    		switch (msg.code) {


    		// wenn fertig dann in Auslauf
    		case LSE2notInterrupted :
    					exit();
    			new(this) BZready;
    			entry();
    			break;





    		}


    		}
    			}

    	}
