/*
 * GegangenUnquittiert.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Hendrik Marquardt
 */

#include "GegangenUnquittiert.h"

void GegangenUnquittiert::entry(){
	actions->redLightBlinkingSlow();
}

void GegangenUnquittiert::exit(){
}

void GegangenUnquittiert::doAction(int event, _pulse msg){
	//perror("Gegangen unquittiert um %d", time());
	//TODO: 10 sekunden noch weiter blinken
	actions->yellowLightBlinking();

	exit();
	//TODO: richtigen übergang wählen
	new(this)BZ;
	entry();
}
