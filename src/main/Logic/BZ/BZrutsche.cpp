/*
 * BZrutsche.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZrutsche.h"
#include "BZEinlauf.h"


void BZrutsche::entry() {
	stateTimer = new SimpleTimer(this->contextData->disp);

	//actions->stopFB();
	cout << "\n  BZrutsche entry\n" << endl;
}
    void BZrutsche::exit() {

    	stateTimer->stopTimer();
    	delete stateTimer;

    	cout << "\n  BZrutsche exit\n" << "in State: "<< stateId << endl;

    	contextData->removeWK();
    	    		//printf("WK count now is: %d",contextData->getWKCount());
    	    		if(contextData->getWKCount()==0) {

    	    			actions->stopFB();
    	    		} else {

    	    		delete this;
    	    		}


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
