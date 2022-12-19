/*
 * BZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "BZ.h"
#include "../RZ/RZ.h"



void BZ::entry(){
	// grünes licht an entry

	printf("in BZ");
	actions->greenOn();

	//actions->greenLightBlinking();

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

				switch (event) {


			   case LSAinterrupted:
				   new (substate) BZEinlauf;
				   substate->entry();
				   break;

			   case ADC_WK_IN_HM:
				   new (substate) BZHoehenmessung;
				   substate->entry();
				//  printf("Werkstuekc in hoehenmesser!!! \n");
				   actions->moveSlower();
				   break;

			   case	ADC_WK_NIN_HM:
				   substate->exit();
				   break;


			   case LSSinterrupted:
				   actions->durchlassen();
				   break;

			   case LSEinterrupted:
				   new (substate) BZAuslauf;
				   substate->entry();
				   break;

			   case LSEnotInterrupted:
				   new (substate) BZready;
				   substate->entry();
				   break;

			   case STPinterrupted:

			  		exit();
			  		new (this) RZ;
			  		entry();
			  		break;


				case ESTP:
					new(this) ESZ;
					entry();
					break;
				}

}

