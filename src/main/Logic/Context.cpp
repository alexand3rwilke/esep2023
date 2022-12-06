/*
 * Context.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#include "Context.h"

#include "Basestate.h"

#include "RZ/RZ.h"
#include "BZ/BZ.h"
#include "ESZ/ESz.h"
#include "SMZ/SMZ.h"
#include "FZ/FZ.h"


Context::Context(Dispatcher *dispatcher, Actions *actions) {

	state = new RZ(); // Idle State
	disp = dispatcher;
	this->actions = actions;


	ContextThread = new std::thread([this]() {eventHandler();});

}

Context::~Context() {
	delete state;
	delete disp;
}

void Context::eventHandler(){
	printf("Context wurde gestartet");


	/* ### Create channel ### */
		int chanID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
		if (chanID < 0) {
			perror("Could not create a channel!\n");
		}

		int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
		if (conID < 0) {
			perror("Could not connect to channel!");
		}

		/*events = {INT_LS_AUS, INT_LS_EIN, INT_LS_HOE,
				INT_LS_RMP, INT_LS_WEI, INT_LS_MET,
				INT_T_EST, INT_T_RES, INT_T_STP, INT_T_STR};
				*/
		events={1,2,3};

		disp->registerForEventWIthConnection(events, conID);

		while (true) {

			_pulse msg;

			int recvid = MsgReceivePulse(chanID, &msg, sizeof(_pulse), nullptr);

			   if (recvid < 0) {
			   			perror("MsgReceivePulse failed!");
			   			//exit(EXIT_FAILURE);
			   			exit();
			   		}

			   switch(msg.code) {

			   case 1:
				   //if (msg.value.sival_int == 1) { !!!!!!!!!!!!!!
					   actions->startFB();
				   //}
				   break;

			   case 2:
				   actions->stopFB();

				   break;

			   case 3:
				   actions->moveFaster();
				   break;

			   case	4:
				   actions->moveSlower();
				   break;

			   case	5:
				   actions->greenOn();
				   break;


			   case	6:
				   actions->greenOff();
				   break;

			   case	7:
				   actions->yellowOn();
				   break;

			   case 8:
				   actions->yellowOff();
			   	   break;

			   case 9:
				   actions->redOn();
				   break;

			   case 10:
				   actions->redOff();
				   break;
			   }


		//		printf("SENSORIK HAT INTERRUPT EHRALTEN!\n");
		}


}

