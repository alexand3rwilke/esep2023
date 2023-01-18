/*
 * FAQZ.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "FAQZ.h"

void FAQZ:: entry(){
	actions->redOn();

}
void FAQZ:: exit(){

}
void FAQZ:: doAction(int event, _pulse msg){
	switch(event){
	case LSR1notInterrupted:
		contextData->setRampe1Voll(false);
		break;
	case LSR2notInterrupted:
		contextData->setRampe2Voll(false);
		break;
	case RSTinterrupted:
		if(contextData->getRampe1Voll() == false && contextData->getRampe2Voll() == false){
			MsgSendPulse(contextData->disp->getConnectionID(),-1,FEHLER_OK,0);
		}
	}
}

