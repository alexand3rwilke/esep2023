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

	printf("in BZ");
	//actions->greenOn();

	actions->greenLightBlinking();
	substate = new BZready();
	substate->setActions(actions);
	substate->entry();
}

void BZ::exit(){
	// grünes licht aus exit
	actions->greenOff();
	actions->stopFB();
}


void BZ::doAction (int event, _pulse msg) {

	///
				// gebe event an substate weiter
				substate->doAction(event, msg);

	//
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


				case ESTP:
					  exit();
					new(this) ESZ;
					entry();
					break;
				}

}

