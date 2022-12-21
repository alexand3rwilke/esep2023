/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */


#include "BZUebergabe.h".h";


void BZUebergabe::entry() {

	cout << "\n  BZUebergabe entry\n" << endl;
	actions->stopFB();
}
    void BZUebergabe::exit() {

    }
    void BZUebergabe::estp() {


    }
    void BZUebergabe::doAction(int event, _pulse msg){


    	switch(event){
    		// check ob LSE interrupt bekommt
    		case LSEnotInterrupted:

    			exit();
    			new(this) BZready;
    			entry();
    			break;
    		}

    	}
