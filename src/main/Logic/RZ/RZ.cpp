/*
 * RZ.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "RZ.h"
#include "../SMZ/SMZ.h"


void RZ::entry() {
	printf("---in rz entry");
	actions->greenOn();
	actions->yellowOff();
	actions->redOff();

}

void RZ::exit() {

}


/**
 * Ruhezustand
 */
void RZ::doAction(int event){

	switch (event) {
		//Starte Betriebszustand
		case STRinterrupted:
			exit();
			new(this) BZ;
			entry();
			break;
		//Starte Servicemode
		case STR_SMZ:
			exit();
			new (this) SMZ;
			entry();
			break;
	}
//			 * Hier wird die Taste Start geprüft, on die lange gedrückt oder schnell gedrückt
//							 * Zeit: 2 Sekunden
//							 * >= : Kalibierung
//							 * < : Betriebzuistand
//							 */
//							if (recvid == 0) {	//pulse received.
//								if(msg.code == T_STR_GDR || msg.code == FBM2_STR_GDR){
//
//									time_t start_time;
//									time_t end_time;
//
//									start_time = time(NULL);
//
//									while(true) {
//										int recvid = MsgReceivePulse(myChannel, &msg, sizeof(_pulse), nullptr);
//
//
//										if (msg.code == T_STR_NGDR || msg.code == FBM2_STR_NGDR) {
//
//											end_time = time(NULL);
//
//											double time_diff = difftime(end_time,start_time);
//
//											if(time_diff >= 2){
//												new(this) KalibrierungIdle;
//												 entry();
//
//											}
//		}
}


void RZ::estp(){
	exit();
	new(this) ESZ;
	entry();

}







