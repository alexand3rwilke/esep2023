/*
 * FAUZ.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "FAUZ.h"

void FAUZ:: entry(){
	actions->redLightBlinking();
}
void FAUZ:: exit(){

}
void FAUZ:: doAction(int event, _pulse msg){
	switch(event){
	case LSR1notInterrupted:
		contextData->setRampe1Voll(false);
		if(contextData->getRampe2Voll()==false){
			exit();
			new (this) FGUZ;
			entry();
		}
		break;
	case LSR2notInterrupted:
		contextData->setRampe2Voll(false);
		if(contextData->getRampe1Voll()==false){
			exit();
			new (this) FGUZ;
			entry();
		}
		break;
	case RSTinterrupted:
		exit();
		new (this) FAQZ;
		entry();
		break;
	}
}

