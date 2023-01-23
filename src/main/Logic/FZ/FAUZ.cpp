/*
 * FAUZ.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "FAUZ.h"

void FAUZ:: entry(){
	cout << "[FZ] Anstehend unquittieren - warte auf RST" << endl;
	actions->redLightBlinking();
}
void FAUZ:: exit(){

}
void FAUZ:: doAction(int event, _pulse msg){
	switch(event){
	case RUTSCHE_1_LEER:
	//	cout << "Rutsche 1: " << contextData->getRampe1Voll() <<" und Rutsche 2: " <<contextData->getRampe2Voll() << endl;
		if(contextData->getRampe1Voll()==false && contextData->getRampe2Voll()==false ){
			exit();
			new (this) FGUZ;
			entry();
		}
		break;
	case RUTSCHE_2_LEER:
	//	cout << "Rutsche 1: " << contextData->getRampe1Voll() <<" und Rutsche 2: " <<contextData->getRampe2Voll() << endl;
		if(contextData->getRampe2Voll()==false && contextData->getRampe1Voll()==false ){
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

