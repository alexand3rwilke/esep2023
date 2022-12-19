/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZready.h"
#include "BZEinlauf.h"


void BZready::entry() {

	cout << "\n  rz entry\n" << endl;
}
    void BZready::exit() {

    }
    void BZready::estp() {


    }
    void BZready::doAction(int event, _pulse msg){


    	switch(event){
    		// check ob LSE interrupt bekommt
    		case LSAinterrupted :

    			exit();
    			new(this) BZEinlauf;
    			entry();
    			break;
    		}

    	}
