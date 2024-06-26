/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */


#include "BZUebergabe.h"
#include "../../Imports.h"



void BZUebergabe::entry() {


	cout << "[BZ] BZUebergabe entry\n" << endl;
	if(contextData->getF2Running()) {
		cout << "Warte .. Festo2 läuft läuft noch! " << endl;
		actions->stopFB();
	}


}
    void BZUebergabe::exit() {

    	cout << "[BZ] BZUebergabe exit\n" << endl;
    	contextData->removeWK();

    	if(contextData->getWKCount() == 0) {
    		actions->stopFB();
    	}


    	MsgSendPulse(contextData->disp->getConnectionID(), -1, WK_TELEPORT, getStateId());
    	//	cout << "Übertrage Werkstueck von State" /* << getStateId() << "an Festp2"<< "\n"*/ << endl;

			if(FESTO_TYPE==1){
				stateTimer->stopTimer();
				stateTimer->resetTimer();
				delete stateTimer;
			}
        	MsgSendPulse(contextData->disp->getConnectionID(), -1, DELETE_STATE, getStateId());
    }
    void BZUebergabe::estp() {


    }
    void BZUebergabe::doAction(int event, _pulse msg){


    	switch(event){
    		// Checke ob WK in LSA von FEsto 2 ist dann stop
    		
			// case LSE1notInterrupted:
    		// 	//actions->stopFB();
    		// 	exit();
    		// 	new(this) BZready;
    		// 	entry();
    		// 	break;




    		case LSA2interrupted:
  			// TODO delete this thread
				exit();
			//	delete this;
				//new(this) BZready;
				//entry();
				break;




    		// case LSE2interrupted:
    		//   			// TODO delete this thread
    		// 	actions->stopFB();
    		// 				exit();
    		// 				new(this) BZready;
    		// 				entry();
    		// 				break;



    		// case LSE1interrupted:
    		//     		  			// TODO delete this thread
    		// 	actions->stopFB();
    		//     						exit();
    		//     						new(this) BZready;
    		//     						entry();
    		//     						break;
    		}








    	}
