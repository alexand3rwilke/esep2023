/*
 * FGUZ.cpp
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#include "FGUZ.h"


void FGUZ:: entry(){
	actions->greenLightBlinking();
	//TimerBZ = new TimerBZ((contextData->disp->getConnectionID(),3,)
	usleep(1000 * (3 * 1000 ));
	MsgSendPulse(contextData->disp->getConnectionID(),-1,FEHLER_OK,0);
}
void FGUZ:: exit(){

}
void FGUZ:: doAction(int event, _pulse msg){
//	switch(event){
//	case LSR1notInterrupted:
//		MsgSendPulse(contextData->disp->getConnectionID(),-1,FEHLER_OK,0);
//	}
}

