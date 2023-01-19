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

	stateTimer = new SimpleTimer(this->contextData->disp);
	    	actions->stopFB();
	    	Werkstueck wk = contextData->getGescanntWKMapForStateForIndex(stateId);
	    	cout << wk.toJsonString() << "kam am ende an" << endl;



}
    void BZAuslauf::exit() {
    	MsgSendPulse(contextData->disp->getConnectionID(), -1, FA2_STOPPED, 0);
    	contextData->removeWK();
    	delete stateTimer;


    	//lösche den State nachdem das WK vom Band genommen wurde
    //	delete this;
    }
    void BZAuslauf::estp() {


    }
    void BZAuslauf::doAction(int event, _pulse){




    		switch (event) {


    		// wenn fertig dann in Auslauf
    		case LSE2notInterrupted :
    			exit();
    			new(this) BZready;
    			entry();
    			break;

    		}





    	}
