/*
 * QnetServer.cpp
 *
 *  Created on: 15.12.2022
 *      Author: Dresske, Christian
 */

#include "QnetServer.h"
#include <stdio.h>
#include "../../Imports.h"
#define STR_MSG   (_IO_MAX + 1)
typedef struct _pulse header_t;

typedef struct {
	int size; // size of data block
	int count; // some counter used by the application
	// further data fields required by our application
} app_header_t;

QnetServer::QnetServer(const char* attach_point, Dispatcher *disp, ContextData  *contextData) {
	//this->data = data;
	this ->dispatcher = disp;
	this->attach_point =attach_point;
	this->contextData = contextData;
	ServerThread = new std::thread([this]() {server();});
}

QnetServer::~QnetServer() {
}

int QnetServer::server(){

	name_attach_t *attach;
	bool serverRunning = false;
	std::mutex mut;
	int chid = 0;


		if(USE_GNS){
			if ((attach = name_attach(NULL, attach_point, NAME_FLAG_ATTACH_GLOBAL)) == NULL) {  // important!! Use "NAME_FLAG_ATTACH_GLOBAL" flag if the other machine should see it !!!
			   perror("[Server] Failed to attach name!");
		    }
			std::cout << "[Server] Channel open with name: " << attach_point << "\n";
			chid = attach->chid;

		}else{
			if((chid = ChannelCreate(0)) < 0 ){
				perror("[Server] Failed to create channel!");
			}
		}

		mut.lock();
		serverRunning = true;
		mut.unlock();

		 while (1) {

//			 if (data->getServerCounter() == 20) {
//				 data->resetServerCounter();
//			 }

			   // Waiting for a message and read first header
			  // _pulse pulse;
			   //int rcvid = MsgReceive (chid, &pulse, sizeof (_pulse), NULL);

			 header_t header;
			 int rcvid = MsgReceive (attach->chid, &header, sizeof (header_t), NULL);


		       if (rcvid == -1) { // Error occurred
		    	   perror("[Server]: MsgReceived failed!");
		           break;
		       }

		       if (rcvid == 0) {// Pulse was received
		    	   switch (header.code) {
		    	   	case _PULSE_CODE_DISCONNECT:
		    	   		printf("[Server] received _PULSE_CODE_DISCONNECT\n");
		    	   	    /* A client disconnected all its connections (called
		    	   	     * name_close() for each name_open() of our name) or
		    	   	     * terminated. */
		    	   	    ConnectDetach(header.scoid);
		    	   	    break;
		    	   	case _PULSE_CODE_UNBLOCK:
		    	   	    printf("[Server] received _PULSE_CODE_UNBLOCK\n");
		    	   	    /* REPLY blocked client wants to unblock (was hit by
		    	   	     * a signal or timed out).  It's up to you if you
		    	   	     * reply now or later. */
		    	   	    break;

					//nur zum Testen
		    	   	// case LSE:
		    	   	// 	MsgSendPulse(dispatcher->getConnectionID(), -1, LSA1interrupted, 0);
		    	   	// 	break;

		    	   	case HELLO:
		    	   		std::cout << "Hallo von anderer Anlage gesendet!\n" << endl ;
		    	   	    break;

		    	   	case LSE1interrupted:
		    	   		if(FESTO_TYPE == 2) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, LSE1interrupted, 0);
		    	   		}
						break;

		    	   	case LSA2interrupted:
		    	   		if(FESTO_TYPE == 1) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, LSA2interrupted, 0);
		    	   		}
		    	   		break;

// ESTP
					case ESTP1interrupted:
		    	   		if(FESTO_TYPE == 2) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, ESTP1interrupted, 0);
		    	   		}
		    	   		break;


		    	   	case ESTP2interrupted:
		    	   		if(FESTO_TYPE == 1) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, ESTP2interrupted, 0);
		    	   		}
		    	   		break;


		    	   	case ESTP1notInterrupted:
					if(FESTO_TYPE == 2) {
						MsgSendPulse(dispatcher->getConnectionID(), -1, ESTP1notInterrupted, 0);
					}
					break;


				case ESTP2notInterrupted:
					if(FESTO_TYPE == 1) {
						MsgSendPulse(dispatcher->getConnectionID(), -1, ESTP2notInterrupted, 0);
					}
					break;

					case LSR1notInterrupted:
		    	   		if(FESTO_TYPE == 2) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, LSR1notInterrupted, 0);
		    	   		}
		    	   		break;

					case LSR2notInterrupted:
		    	   		if(FESTO_TYPE == 1) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, LSR2notInterrupted, 0);
		    	   		}
		    	   		break;

					case LSR1interrupted:
		    	   		if(FESTO_TYPE == 2) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, LSR1interrupted, 0);
		    	   		}
		    	   		break;

					case LSR2interrupted:
		    	   		if(FESTO_TYPE == 1) {
		    	   			MsgSendPulse(dispatcher->getConnectionID(), -1, LSR2interrupted, 0);
		    	   		}
		    	   		break;

					case ESTP1Finished:
						if(FESTO_TYPE == 2) {
					MsgSendPulse(dispatcher->getConnectionID(), -1, ESTP1Finished, 0);

						}
					break;

					case ESTP2Finished:
						if(FESTO_TYPE == 1) {
					MsgSendPulse(dispatcher->getConnectionID(), -1, ESTP2Finished, 0);
						}
					break;

					case FA2_RUNNING:
					if(FESTO_TYPE == 1) {
						cout << "recieved MESSAGE FA2_RUNNING!!!!" << endl;
						MsgSendPulse(dispatcher->getConnectionID(), -1, FA2_RUNNING, 0);
					}
					break;

					case FA2_STOPPED:
						if(FESTO_TYPE == 1) {
						MsgSendPulse(dispatcher->getConnectionID(), -1, FA2_STOPPED, 0);
						}
						break;

					case FEHLER_2:
						if(FESTO_TYPE == 1) {
						MsgSendPulse(dispatcher->getConnectionID(), -1, FEHLER_2, 0);
					}
					break;
					case FEHLER_1:
						if(FESTO_TYPE == 2) {
						MsgSendPulse(dispatcher->getConnectionID(), -1, FEHLER_1, 0);
					}
					break;
					case LSE1notInterrupted:
						if(FESTO_TYPE == 2) {
							MsgSendPulse(dispatcher->getConnectionID(), -1, LSE1notInterrupted, 0);
						}
						break;



//					case FBM2_SEND_WK:
//
//						int recvid = MsgReceivePulse (chid, &pulse, sizeof (_pulse), NULL);
//
//						switch (pulse.code) {
//							case FBM1_WK_FLACH: data->getWerkstueck(data->getServerCounter()).typ2 = FLACH; data->getWerkstueck(data->getServerCounter()).Hoehe2 = pulse.value.sival_int;   break;
//							case FBM1_WK_NORMAL: data->getWerkstueck(data->getServerCounter()).typ2 = NORMAL;  data->getWerkstueck(data->getServerCounter()).Hoehe2 = pulse.value.sival_int;  break;
//							case FBM1_WK_BOHRUNG: data->getWerkstueck(data->getServerCounter()).typ2 = BOHRUNG;  data->getWerkstueck(data->getServerCounter()).Hoehe2 = pulse.value.sival_int;  break;
//							case FBM1_WK_METALL: data->getWerkstueck(data->getServerCounter()).typ2 = METALL; data->getWerkstueck(data->getServerCounter()).metall2 = METALL;  data->getWerkstueck(data->getServerCounter()).Hoehe2 = pulse.value.sival_int; break;
//							case FBM1_WK_CODIERT_GRADE: data->getWerkstueck(data->getServerCounter()).typ2 = GRADECODIERT;  data->getWerkstueck(data->getServerCounter()).Hoehe2 = pulse.value.sival_int;  break;
//							case FBM1_WK_CODIERT_UNGRADE: data->getWerkstueck(data->getServerCounter()).typ2 = UNGRADECODIERT;  data->getWerkstueck(data->getServerCounter()).Hoehe2 = pulse.value.sival_int;  break;
//							case FBM1_WK_CODIERT_NULL: data->getWerkstueck(data->getServerCounter()).typ2 = NULLCODIERT;  data->getWerkstueck(data->getServerCounter()).Hoehe2 = pulse.value.sival_int;  break;
//						}
//						data->increaseServerCounter();
		    	   }

		       }

		       if ((_IO_BASE <= header.type) && (header.type <= _IO_MAX)) {
				   // Some QNX IO msg generated by gns was received
				   if (header.type == _IO_CONNECT ) {
						// QNX IO msg _IO_CONNECT was received; answer with EOK
						printf("[Server] received _IO_CONNECT (sync. msg) \n");
						MsgReply( rcvid, EOK, NULL, 0 );
				   }

		       }
		       if (STR_MSG == header.type && FESTO_TYPE == 2) {
		       			   		// printf("Server: STR_MSG received.\n");
		       			   		// read app header
		       			   		app_header_t app_header;
		       			   		MsgRead(rcvid, &app_header, sizeof(app_header), sizeof(header_t));
		       			   		// ToDo return value of MsgRead must be checked, in particular number of read bytes

		       			   		// read payload
		       			   		//char * buf = malloc(app_header.size);
		       			   		char buf[app_header.size];
		       			   		// ToDo return value of malloc must be checked

		       			   		MsgRead(rcvid, buf, app_header.size, sizeof(header_t) + sizeof(app_header_t));
		       			   		// ToDo return value of MsgRead must be checked, in particular number of read bytes

		       			   		printf("Server: got the STR_MSG (count = %d): %s \n", app_header.count, buf);
		       			   		// TODO HIER DANN WK ANLEGEN AUS DEM STRING
		       			   		string wkJsonString;
		       			   		wkJsonString.assign(buf, sizeof(buf));
		       			   		Werkstueck *wk = new Werkstueck(wkJsonString);
		       			   		contextData->setGescanntWKMapForStateForIndex(0,wk->werkstueckTyp, wk->mittlereHoehe,wk->wkFlipped,wk->aussortieren,wk->absoluteHoehe);

		       			   		MsgReply(rcvid, EOK, NULL, 0);
		       			   		//free(buf);
		       			   	}



		 }
		 return 1;

}


