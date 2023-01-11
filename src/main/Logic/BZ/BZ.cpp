/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"
#include "../RZ/RZ.h"
#include "../ESZ/ESZ.h"


void BZ::entry(){
	// grünes licht an entry
	actions->greenOn();
	printf("in BZ");
	actions->greenOn();
	substate = new BZready();
	substate->setActions(actions);
	substate->setContextData(contextData);
	substate->entry();
	//substate->contextData;

}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff();
	actions->stopFB();
}


void BZ::doAction (int event, _pulse msg) {

//	for(int i =0; i < 2; i++){
//		Basestate *tmp= &state1;
//		i++;

		switch (event) {

	   case ESTPinterrupted:
		   exit();
		   new (this) ESZ;
		   entry();
		   break;


	   case STPinterrupted:
		   exit();
			new (this) RZ;
			entry();
			break;

		case STRinterrupted:
			  exit();
			new(this) BZ;
			entry();
			break;
		case LSAinterrupted:
			//Thread starten
//			if(i== 0){
//
//			}
//			tmp = new BZready();
			substate->setActions(actions);
			substate->setContextData(contextData);
			substate->entry();
			substate->doAction(event, msg);
			break;
		default:
			//cout << event << ":  FSM Nr." << i << endl;
			// gebe event an substate weiter
			substate->doAction(event, msg);

		}
//	}


//				switch (event) {
//				case LSAinterrupted:
//					//Thread starten
//					substate = new BZready();
//					substate->setActions(actions);
//					substate->setContextData(contextData);
//					substate->entry();
//					substate->doAction(event, msg);
//					break;
//
//			   case ESTPinterrupted:
//				   exit();
//				   new (this) ESZ;
//				   entry();
//				   break;
//
//
//			   case STPinterrupted:
//				   exit();
//			  		new (this) RZ;
//			  		entry();
//			  		break;
//
//				case STRinterrupted:
//					  exit();
//					new(this) BZ;
//					entry();
//					break;
//				default:
//					// gebe event an substate weiter
//					substate->doAction(event, msg);
//
//				}

}

