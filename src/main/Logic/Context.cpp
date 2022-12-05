/*
 * Context.cpp
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#include "Context.h"

#include "BaseState.h"
#include "RZ/RZ.h"
#include "BZ/BZ.h"
#include "ESZ/ESz.h"
#include "SMZ/SMZ.h"
#include "FZ/FZ.h"


Context::Context(Dispatcher dispatcher) {

	state = new RZ(); // Idle State
	dispa = dispatcher;

	ContextThread = new std::thread([this]() {eventHandler();});

}

Context::~Context() {
	delete state;
	delete dispa;
}

Context::eventHandler(){
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
		event

		disp->registerEventAndConnection(events, coID);

		while (true) {

			_pulse msg;

			int recvid = MsgReceivePulse(chid, &msg, sizeof(_pulse), nullptr);

			   if (recvid < 0) {
			   			perror("MsgReceivePulse failed!");
			   			exit(EXIT_FAILURE);
			   		}

			   switch(msg.code) {

			   case INT_LS_AUS:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_AUS_NDURCH, 0);
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_AUS_DURCH, 0);
				   } break;

			   case INT_LS_EIN:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_EIN_NDURCH, 0);
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_EIN_DURCH, 0);
				   } break;

			   case INT_LS_HOE:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_HE_NDURCH, 0);
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_HE_DURCH, 0);
				   } break;

			   case	INT_LS_RMP:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_RMP_NDURCH, 0);
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_RMP_DURCH, 0);
				   } break;

			   case	INT_LS_WEI:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_WEI_NDURCH, 0);
					   break;
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_WEI_DURCH, 0);
					   break;
				   }

			   case	INT_LS_MET:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, WK_METAL, 0);
					   break;
				   }	else {

					   break;
				   }

			   case	INT_T_EST:
			   	   if (msg.value.sival_int == 1) {
			   		MsgSendPulse(disp->conIDDispatcher, -1, T_EST_NGDR, 0);
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, T_EST_GDR, 0);
				   } break;

			   case INT_T_RES:
			   	   if (msg.value.sival_int == 1) {
			   		 MsgSendPulse(disp->conIDDispatcher, -1, T_RES_GDR, 0);
				   }	else {
					  MsgSendPulse(disp->conIDDispatcher, -1, T_RES_NGDR, 0);
				   } break;

			   case INT_T_STP:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, T_STP_NGDR, 0);
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, T_STP_GDR, 0);
				   } break;

			   case INT_T_STR:
				   if (msg.value.sival_int == 1) {
					   MsgSendPulse(disp->conIDDispatcher, -1, T_STR_GDR, 0);
				   }	else {
					   MsgSendPulse(disp->conIDDispatcher, -1, T_STR_NGDR, 0);
				   } break;


			   }


		//		printf("SENSORIK HAT INTERRUPT EHRALTEN!\n");
		}


}

