/*
 * QnetClient.cpp
 *
 *  Created on: 15.12.2022
 *  Author: Dresske, Christian
 */

#include "QnetClient.h"
#include "../../Imports.h"

QnetClient::QnetClient(const char* attach_point, Dispatcher *disp) {

	this->dispatcher = disp;
	this->attach_point =attach_point;
	ClientThread = new std::thread([this]() {client();});
}

QnetClient::~QnetClient() {}

int QnetClient::client(){

	// der andere Server sollte dann bereit sein
	sleep(10);

	//// ======== connect to channel ================
	int server_coid;

	// Use GNS for setting up the connection to the server - running somewhere in the network
	if ((server_coid = name_open(attach_point, NAME_FLAG_ATTACH_GLOBAL)) == -1) {
	    	perror("Client: name_open failed");
	        return EXIT_FAILURE;
	}

	//// ======== send pulse message ================
    if(MsgSendPulse(server_coid,-1,HELLO,0) != 0){
		 	perror("[Client]: sendPulse failed");
		 	return EXIT_FAILURE;
	}

	/* ### Create channel ### */
	int channnelID = ChannelCreate(0);//Create channel to receive Events

	if (channnelID < 0) {
		perror("Could not create a channel!\n");

	}

	int pid = getpid();
	int conID = ConnectAttach(0, pid, channnelID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.

	if (conID < 0) {
				perror("Could not connect to channel!");
	}

	vector<int8_t> events = {LSE, LSE1interrupted, LSA2interrupted};

	dispatcher->registerForEventWIthConnection(events, conID);

	_pulse msg;

	while (true) {

//				if (data->getClientCounter() == 20) {
//					data->resetClientCounter();
//	}

		int recvid = MsgReceivePulse(channnelID, &msg, sizeof(_pulse), nullptr);

		switch(msg.code){

//					case LSE1:
//
//					if(MsgSendPulse(server_coid, -1, LSE,0) != 0){
//						perror("[Client]: sendPulse failed");
//						return EXIT_FAILURE;
//						}
//					break;




					case LSE1interrupted:

					if(MsgSendPulse(server_coid, -1, LSE1interrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;



					case LSA2interrupted:

					if(MsgSendPulse(server_coid, -1, LSA2interrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;

	//				case WK_DATA_SEND:
	//
	//					if(MsgSendPulse(server_coid, -1, FBM2_SEND_WK,data->getClientCounter()) != 0){
	//						perror("[Client]: sendPulse failed");
	//						return EXIT_FAILURE; }
	//					else {
	//						 	Werkstueck wk = data->getWerkstueck(data->getClientCounter());
	//						 	Typ tp = wk.typ1;
	//						 	switch (tp) {
	//
	//						 		case FLACH: MsgSendPulse(server_coid, -1, FBM1_WK_FLACH, wk.Hoehe1);  break;
	//						 		case NORMAL: MsgSendPulse(server_coid, -1, FBM1_WK_NORMAL, wk.Hoehe1); break;
	//						 		case BOHRUNG: MsgSendPulse(server_coid, -1, FBM1_WK_BOHRUNG, wk.Hoehe1); break;
	//						 		case METALL: MsgSendPulse(server_coid, -1, FBM1_WK_METALL, wk.Hoehe1); break;
	//						 		case GRADECODIERT: MsgSendPulse(server_coid, -1, FBM1_WK_CODIERT_GRADE, wk.Hoehe1); break;
	//						 		case UNGRADECODIERT: MsgSendPulse(server_coid, -1, FBM1_WK_CODIERT_UNGRADE, wk.Hoehe1); break;
	//						 		case NULLCODIERT: MsgSendPulse(server_coid, -1, FBM1_WK_CODIERT_NULL, wk.Hoehe1); break;
	//						 	}
	//
	//						 	data->increaseClientCounter();
	//					 }
	//				     break;

			}

	}


	 //// ======== close connection ================

//		 if(USE_GNS){
//
//		 		if(name_close(server_coid) != 0){
//		 			perror("[Client] name_close failed");
//		 		}
//
//
//		 	}else{
//		 		// closes the connection to the server. Sends _PULSE_CODE_DISCONNECT to the server.
//		 		if ((ConnectDetach(server_coid)) != 0) {
//		 			perror("[Client] ConnectDetach failed");
//		 			return EXIT_FAILURE;
//		 		}
//		 	}

		 return 1;

}
