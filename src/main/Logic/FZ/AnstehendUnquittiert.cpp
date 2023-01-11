/*
 * AnstehendUnquittiert.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Hendrik Marquardt
 */

#include "AnstehendUnquittiert.h"

void AnstehendUnquittiert::entry(){
	actions->redLightBlinkingFast();
	perror("ERROR");
}

void AnstehendUnquittiert::exit(){
}

void AnstehendUnquittiert::doAction(int event, _pulse msg){


	switch(event){

	case RSTinterrupted:
		exit();
		new(this)AnstehendQuittiert;
		entry();
		break;

	case LSR1notInterrupted:
		exit();
		new(this)GegangenUnquittiert;
		entry();
		break;
	}
}





