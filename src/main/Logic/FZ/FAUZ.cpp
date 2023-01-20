/*
 * FAUZ.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "FAUZ.h"

void FAUZ:: entry(){
	cout << "entry FZ Anstehend quittieren" << endl;
	actions->redLightBlinking();
}
void FAUZ:: exit(){

}
void FAUZ:: doAction(int event, _pulse msg){
	switch(event){
	case RUTSCHE_1_LEER:
		if(contextData->getRampe2Voll()==false){
			exit();
			new (this) FGUZ;
			entry();
		}
		break;
	case RUTSCHE_2_LEER:

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

