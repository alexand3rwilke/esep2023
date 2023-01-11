/*
 * AnstehendQuittiert.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Hendrik Marquardt
 */

#include "AnstehendQuittiert.h"

void AnstehendQuittiert::entry(){
	actions->redOn();
	perror("OK");

}

void AnstehendQuittiert::exit(){
	actions->redOff();
}

void AnstehendQuittiert::doAction(int event, _pulse msg){

	switch(event){

	if(ruVoll == 0 && rstCounter == 0){
		exit();
		//TODO: richtigen Übergang wählen
		new(this)BZ;
		entry();
	}

	case RU_VOLL:
		ruVoll = 2;
		break;

	case WSZuVielOderWSZuWenig:

		break;

	case LSR1notInterrupted:
		ruVoll--;
		break;

	case LSR2notInterrupted:
		ruVoll--;
		break;

	case RST:
		rstCounter--;
		break;
	}
}
