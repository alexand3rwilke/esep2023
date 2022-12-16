/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZHoehenmessung.h"
#include "BZAussortierer.h"



void BZHoehenmessung::entry() {


}
    void BZHoehenmessung::exit() {

    }
    void BZHoehenmessung::estp() {


    }
    void BZHoehenmessung::doAction(int event){

    	_pulse msg;
    	int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);

    	if (recvid < 0) {
    				perror("MsgReceivePulse failed!");
    			}

    			if (recvid == 0) {
    			while(true) {

    		switch (msg.code) {


    		// wenn fertig dann in Auslauf
    		case 12 :	new(this) BZAussortierer;
    					entry();
    					break;





    		}


    		}
    			}

    	}
