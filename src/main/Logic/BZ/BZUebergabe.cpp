/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */


#include "BZUebergabe.h";
#include "../../Imports.h"


void BZUebergabe::entry() {

	cout << "\n  BZUebergabe entry\n" << endl;



}
    void BZUebergabe::exit() {

    }
    void BZUebergabe::estp() {


    }
    void BZUebergabe::doAction(int event, _pulse msg){


    	switch(event){
    		// Checke ob WK in LSA von FEsto 2 ist dann stop
    		case LSE1notInterrupted:
    			//actions->stopFB();
    			exit();
    			new(this) BZready;
    			entry();
    			break;




    		case LSA2interrupted:
  			// TODO delete this thread
				exit();
				new(this) BZready;
				entry();
				break;




    		case LSE2interrupted:
    		  			// TODO delete this thread
    			actions->stopFB();
    						exit();
    						new(this) BZready;
    						entry();
    						break;



    		case LSE1interrupted:
    		    		  			// TODO delete this thread
    			actions->stopFB();
    		    						exit();
    		    						new(this) BZready;
    		    						entry();
    		    						break;
    		}








    	}
