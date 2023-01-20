/*
 * FAQZ.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "FAQZ.h"

void FAQZ:: entry(){
	cout << "[FZ] Anstehend quittieren" << endl;
	actions->redOn();

}
void FAQZ:: exit(){

}
void FAQZ:: doAction(int event, _pulse msg){
	switch(event){
//	case RUTSCHE_1_LEER:
//		contextData->setRampe1Voll(false);
//		break;
//	case RUTSCHE_2_LEER:
//		contextData->setRampe2Voll(false);
//		break;
	case RSTinterrupted:
		if(contextData->getRampe1Voll() == false && contextData->getRampe2Voll() == false){
			MsgSendPulse(contextData->disp->getConnectionID(),-1,FEHLER_OK,0);
		}
	}
}

