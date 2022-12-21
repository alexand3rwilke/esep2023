/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZAuslauf.h"
#include "BZAussortierer.h"
#include "BZUebergabe.h"
#include "BZ.h"



void BZAussortierer::entry() {

	//TODO MUSS NOCH ANGEPAST WERDEN
	cout << "\n  BZAussortierer entry\n" << endl;



}
    void BZAussortierer::exit() {

    }
    void BZAussortierer::estp() {


    }
    void BZAussortierer::doAction(int event, _pulse msg){
//
//    		// wenn fertig dann in Auslauf


    	switch (event) {
    		case LSEinterrupted :
    			exit();
    			new(this) BZUebergabe;
    			entry();
    			break;


    		case LSSinterrupted :
    			actions->durchlassen();
    			break;



    		case LSE2interrupted :
    		    exit();
    		    actions->stopFB();
    		    new (this) BZready;
    		    entry();


    		}

	}
