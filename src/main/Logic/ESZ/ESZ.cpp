/*
 * ESZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "ESZ.h"


void ESZ::entry(){
	//Was bereits in Aktorik direkt gemacht wird
	//AMP Rot
	//FB Stopp
	resetCounter = 0;
	actions->ampAllOff();
	actions->stopFB();
	actions->redLightBlinking();
	actions->yellowLightBlinking();

	estp1Finished = false;
	estp2Finished = false;


	// substate GUFZ

}

void ESZ::exit(){
	actions->moveFaster();

}

void ESZ::doAction(int event, _pulse msg){

	switch(event){

	case ESTP2notInterrupted:
		schalter2Gedrueckt = false;
		break;

	case ESTP1notInterrupted:
		schalter1Gedrueckt = false;
	break;

	case ESTP1interrupted:
		entry();
		if(FESTO_TYPE == 1) {
			schalter1Gedrueckt = true;
			schalter2Gedrueckt = false;
		} else if(FESTO_TYPE == 2) {
			schalter1Gedrueckt = true;
			schalter2Gedrueckt = false;

		}
		break;

	case ESTP2interrupted:
		entry();
		if(FESTO_TYPE == 2) {
			schalter2Gedrueckt = true;
			schalter1Gedrueckt = false;
		} else if(FESTO_TYPE == 1) {
			schalter2Gedrueckt = true;
			schalter1Gedrueckt = false;

		}

		break;

	case RSTinterrupted:

		//cout << "ESTP1 ist:" << schalter1Gedrueckt << "und ESTP2 ist :" << schalter1Gedrueckt << endl;
		if(!schalter1Gedrueckt && !schalter2Gedrueckt) {
		if(resetCounter == 0){
			actions->redOff();
			actions->yellowOn();
			resetCounter++;
		} else if(resetCounter == 1 && (!schalter1Gedrueckt && !schalter2Gedrueckt)){

			actions->yellowOff();
			resetCounter++;

			if(FESTO_TYPE == 1) {
				MsgSendPulse(contextData->disp->getConnectionID(), -1, ESTP1Finished, 0);
				estp1Finished = true;
					} else if(FESTO_TYPE == 2) {
				MsgSendPulse(contextData->disp->getConnectionID(), -1, ESTP2Finished, 0);
				estp2Finished = true;
					}


			//Todo check wenn keine fehler

		}

		}
	break;

	case STRinterrupted:

		//cout << "Resetcounter is :" << resetCounter << "und beide ESTP done: " << (estp1Finished && estp2Finished) << endl;
		if(resetCounter >= 2 && (estp1Finished && estp2Finished)) {
			exit();
			actions->greenOn();
			new (this) BZ;


		}
		break;


	case ESTP1Finished :
		estp1Finished = true;
		break;

	case ESTP2Finished :
		estp2Finished = true;
		break;
	}





}

