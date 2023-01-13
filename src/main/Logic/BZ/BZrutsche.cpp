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

    }
    void BZrutsche::estp() {


    }
    void BZrutsche::doAction(int event, _pulse msg){


    	switch(event){

    	case LSR1interrupted :
    		//printf("WK count is: %d",contextData->getWKCount());
    		contextData->removeWK();
    		//printf("WK count now is: %d",contextData->getWKCount());
    		if(contextData->getWKCount()==0) {

    			actions->stopFB();
    		} else {

    		delete this;
    		}





    	}




    	}
