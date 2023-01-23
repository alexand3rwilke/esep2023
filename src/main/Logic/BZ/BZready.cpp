/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZready.h"
#include "BZEinlauf.h"


void BZready::entry() {

	//actions->stopFB();
	cout << "\n  BZready entry\n" << endl;
}
    void BZready::exit() {

    }
    void BZready::estp() {


    }
    void BZready::doAction(int event, _pulse msg){


    	switch(event){
    		// check ob LSE interrupt bekommt
    		case LSA1interrupted :

    			exit();
    			new(this) BZEinlauf;
    			entry();
    			break;


    		case LSA2interrupted :

				exit();
				new(this) BZEinlauf;
				entry();
				break;



    		case LSE1interrupted :

				exit();
				new(this) BZEinlauf;
				entry();
				break;


    		case LSE1notInterrupted:
    			if(FESTO_TYPE ==2 /*&& !contextData->getF2Running()*/){
    				actions->startFB();
    			}
    			break;


    		// case LSE2interrupted :

			// 	exit();
			// 	new(this) BZEinlauf;
			// 	entry();
			// 	break;

    	}




    	}
