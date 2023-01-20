/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */


#include "BZAuslauf.h"
#include "BZready.h"
#include "../../MQTTpublish/MQTTpublish/MQTTpublish.h"



void BZAuslauf::entry() {

	string stringForMQTT = contextData->getGescanntWKMapForStateForIndex(stateId).toJsonString();
	stringForMQTT = "Mqtt mit Dispatchtecher";
	mqtt->sendToConsole(stringForMQTT);
	usleep(1000 * (2 * 1000 ));
	MsgSendPulse(contextData->disp->getConnectionID(),-1,MQTTMESSAGE,0);



	cout << "\n  BZAuslauf entry\n" << endl;

	stateTimer->startTimer();
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
