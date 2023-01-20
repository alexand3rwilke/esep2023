/*
 * BZrutsche.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZrutsche.h"
#include "BZEinlauf.h"


void BZrutsche::entry() {


	//actions->stopFB();
	cout << "\n  BZrutsche entry\n" << endl;
}
    void BZrutsche::exit() {



    	cout << "\n  BZrutsche exit\n" << "in State: "<< stateId << endl;

    	contextData->removeWK();
    	    		//printf("WK count now is: %d",contextData->getWKCount());
    	    		if(contextData->getWKCount()==0) {

    	    			actions->stopFB();
    	    		}


    	    				//stateTimer->stopTimer();
    	    		        	stateTimer->resetTimer();
    	    		        	//delete stateTimer;
    	    		        	if(FESTO_TYPE == 2) {
    	    		        		MsgSendPulse(contextData->disp->getConnectionID(), -1, FA2_STOPPED, 0);
    	    		        	}

    	    		        	MsgSendPulse(contextData->disp->getConnectionID(), -1, DELETE_STATE, getStateId());

    }
    void BZrutsche::estp() {


    }
    void BZrutsche::doAction(int event, _pulse msg){


    	switch(event){

    	case LSR1interrupted :
    		//printf("WK count is: %d",contextData->getWKCount());
    		exit();

     	case LSR2interrupted :
        	//printf("WK count is: %d",contextData->getWKCount());
        	exit();




    	}




    	}
