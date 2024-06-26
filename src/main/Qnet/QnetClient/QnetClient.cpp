/*
 * QnetClient.cpp
 *
 *  Created on: 15.12.2022
 *  Author: Dresske, Christian
 */

#include "QnetClient.h"
#include "../../Imports.h"

typedef struct {
int size; // size of data block
int count; // some counter used by the application

} app_header_t;
typedef struct _pulse header_t;

app_header_t app_header;
iov_t iov[3]; // m
header_t  header;
char  r_msg[512]; // buffer for the answer


#define STR_MSG   (_IO_MAX + 1)
#define DATA_MSG  (_IO_MAX + 2)

QnetClient::QnetClient(const char* attach_point, Dispatcher *disp,ContextData  *contextData) {

	this->contextData = contextData;
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

	vector<int8_t> events = {LSE, LSE1interrupted,LSE1notInterrupted, LSA2interrupted,ESTP1interrupted, ESTP2interrupted,LSR1notInterrupted,LSR2notInterrupted,LSR1interrupted,LSR2interrupted,
								ESTP1Finished,ESTP2Finished,ESTP1notInterrupted,ESTP2notInterrupted,FA2_RUNNING,FA2_STOPPED, FEHLER_1, FEHLER_2,WK_TELEPORT};


	dispatcher->registerForEventWIthConnection(events, conID);

	_pulse msg;

	while (true) {

//				if (data->getClientCounter() == 20) {
//					data->resetClientCounter();
//	}

		int recvid = MsgReceivePulse(channnelID, &msg, sizeof(_pulse), nullptr);

		switch(msg.code){

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

					case ESTP1interrupted:

					if(MsgSendPulse(server_coid, -1, ESTP1interrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;			

					case ESTP2interrupted:

					if(MsgSendPulse(server_coid, -1, ESTP2interrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;	



					case ESTP1notInterrupted:

						if(MsgSendPulse(server_coid, -1, ESTP1notInterrupted,0) != 0){
							perror("[Client]: sendPulse failed");
							return EXIT_FAILURE;
							}
						break;

					case ESTP2notInterrupted:

					if(MsgSendPulse(server_coid, -1, ESTP2notInterrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;


					case LSR1notInterrupted:
					if(MsgSendPulse(server_coid, -1, LSR1notInterrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;	

					case LSR2notInterrupted:
					if(MsgSendPulse(server_coid, -1, LSR2notInterrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;

					case LSR1interrupted:
					if(MsgSendPulse(server_coid, -1, LSR1interrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;	


					case LSR2interrupted:
					if(MsgSendPulse(server_coid, -1, LSR2interrupted,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;



					case ESTP1Finished :

					if(MsgSendPulse(server_coid, -1, ESTP1Finished,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
						break;



					case ESTP2Finished :

					if(MsgSendPulse(server_coid, -1, ESTP2Finished,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
						break;


					case FA2_RUNNING :

					if(MsgSendPulse(server_coid, -1, FA2_RUNNING,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
						break;


					case FA2_STOPPED :

					if(MsgSendPulse(server_coid, -1, FA2_STOPPED,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
						break;
					case FEHLER_1 :

					if(MsgSendPulse(server_coid, -1, FEHLER_1,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;
					case FEHLER_2 :

					if(MsgSendPulse(server_coid, -1, FEHLER_2,0) != 0){
						perror("[Client]: sendPulse failed");
						return EXIT_FAILURE;
						}
					break;

					case LSE1notInterrupted:
						if(MsgSendPulse(server_coid, -1, LSE1notInterrupted,0) != 0){
							perror("[Client]: sendPulse failed");
							return EXIT_FAILURE;
							}
						break;


					case WK_TELEPORT :

						Werkstueck wk = contextData->getGescanntWKMapForStateForIndex(msg.value.sival_int);
						string wkJson = wk.toString();
						cout << wkJson << endl;

						char payload[200];                      // use dummy values as payload
						memset(payload,0,200);
						strcat(payload,wkJson.c_str());
						int payload_size;                       // +1 due to \0 at the end of a string
						payload_size = sizeof(payload)+1;
						// Compose the msg using an IOV
						header.type = STR_MSG;    // define msg type
						header.subtype = 0x00;

						app_header.size = payload_size;	// fill application header
						app_header.count = 0;

						SETIOV(iov+0, &header, sizeof(header));
						SETIOV(iov+1, &app_header, sizeof(app_header));
						SETIOV(iov+2, payload, payload_size);

						// send msg
						if (-1 == MsgSendvs(server_coid, iov, 3, r_msg, sizeof(r_msg))){
							perror("Client: MsgSend failed");
							//exit(EXIT_FAILURE);
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
	//						 		case UNDEFINED_WK: MsgSendPulse(server_coid, -1, FBM1_WK_CODIERT_NULL, wk.Hoehe1); break;
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
