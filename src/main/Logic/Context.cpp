/*
 * Context.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "Context.h"
#include "ContextData.h"
#include "Basestate.h"

#include "RZ/RZ.h"
#include "BZ/BZ.h"
#include "ESZ/ESz.h"
#include "SMZ/SMZ.h"
#include "FZ/FZ.h"

#include <stdio.h>
#include <iostream>


Context::Context(Dispatcher *dispatcher, Actions *actions, ContextData  *contextData) {


	printf("bin in context");
	state = new RZ(); // Setze state auf ruhezustand
	disp = dispatcher;
	this->contextData = contextData;
	this->actions = actions;
	this-> events = nullptr;
	ContextThread = new std::thread([this]() {eventHandler();});

}

Context::~Context() {
	delete state;
	delete disp;
}



void Context::eventHandler(){


	// Gehe in die Entry methode die von Ruhezustand implementiert wird
	state -> entry();
//	printf("Context wurde gestartet");
//
//
//	/* ### Create channel ### */
//		int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
//		if (chanID < 0) {
//			perror("Could not create a channel!\n");
//		}
//
//		int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
//		if (conID < 0) {
//			perror("Could not connect to channel!");
//		}
//
//		/*events = {INT_LS_AUS, INT_LS_EIN, INT_LS_HOE,
//				INT_LS_RMP, INT_LS_WEI, INT_LS_MET,
//				INT_T_EST, INT_T_RES, INT_T_STP, INT_T_STR};
//				*/
//		events={1,2,3};
//
//		disp->registerForEventWIthConnection(events, conID);
//
//		while (true) {
//
//			_pulse msg;
//
//			int recvid = MsgReceivePulse(chanID, &msg, sizeof(_pulse), nullptr);
//
//			   if (recvid < 0) {
//			   			perror("MsgReceivePulse failed!");
//			   			//exit(EXIT_FAILURE);
//			   			//exit();
//			   		}
//
//			   switch(msg.code) {
//
//			   case 1:
//				   //if (msg.value.sival_int == 1) { !!!!!!!!!!!!!!
//					   actions->startFB(conID);
//				   //}
//				   break;
//
//			   case 2:
//				   actions->stopFB(conID);
//
//				   break;
//
//			   case 3:
//				   actions->moveFaster(conID);
//				   break;
//
//			   case	4:
//				   actions->moveSlower(conID);
//				   break;
//
//			   case	5:
//				   actions->greenOn(conID);
//				   break;
//
//
//			   case	6:
//				   actions->greenOff(conID);
//				   break;
//
//			   case	7:
//				   actions->yellowOn(conID);
//				   break;
//
//			   case 8:
//				   actions->yellowOff(conID);
//			   	   break;
//
//			   case 9:
//				   actions->redOn(conID);
//				   break;
//
//			   case 10:
//				   actions->redOff(conID);
//				   break;
//			   }
//
//
//		//		printf("SENSORIK HAT INTERRUPT EHRALTEN!\n");
//		}
//
//
}

