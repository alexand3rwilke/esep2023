/*
 * WarteAufFlachesWS.cpp
 *
 *  Created on: 16.01.2023
 *      Author: Jobut
 */

#include "WarteAufFlachesWS.h"

void Warte_Auf_Flaches_WS::entry(){
	actions->yellowLightBlinking();
}

void Warte_Auf_Flaches_WS::exit(){


}

void Warte_Auf_Flaches_WS::doAction(int event,_pulse msg){

	switch(event){
	case LSA1interrupted:
		actions->startSMZ_hoehe();
		actions->redOn();
		break;
	}

}

