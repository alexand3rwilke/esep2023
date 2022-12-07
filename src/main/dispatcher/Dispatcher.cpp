
/*
 * DispatcherC.cpp
 *
 *  Created on: 15.11.22
 *      Author: Alexander Wilke; Marquahe
 *
 */
#include "Dispatcher.h"




Dispatcher::Dispatcher() {
		DispThread = new std::thread([this]() {ListenForEvents();});

		//mutex connectionMutex;
}

Dispatcher::~Dispatcher() {
}

void Dispatcher::DispatchMessageToSubscriber(int8_t code, int value) {

	connectionMutex.lock();

		connections = connectionMap[code];
		// Send Value x to all subscribers of the code
		for (u_int j = 0; j < connections.size(); j++) {
			//cout << "sending Mail\n" <<endl;
			MsgSendPulse(connections.at(j), -1, code, value);
		}
	connectionMutex.unlock();
}

void Dispatcher::registerForEventWIthConnection(std::vector<int8_t> events, int conId) {

	connectionMutex.lock();

	// register to get events, puit connectionId in the subscribers list for an event code
	for (u_int i = 0; i < events.size(); i++) {
		// put connection id in every event map it wants to regsiter
		connectionMap[events.at(i)].push_back(conId);
	}
	connectionMutex.unlock();
}



void Dispatcher::ListenForEvents() {

	int channelID = ChannelCreate(0);
	if (channelID < 0) {
		perror("Could not create a channel!\n");

	}
int pid = getpid();
	int conID = ConnectAttach(0, pid, channelID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
	if (conID < 0) {
		perror("Could not connect to channel!");
	}

	chanID = channelID;
	conIDDispatcher =conID ;

	_pulse pulse;

	// run 4ever
	 while (true) {

		 	 //
		 int recvid = MsgReceivePulse(channelID, &pulse, sizeof(_pulse), nullptr);

		 		if (recvid < 0) {
		 			perror("MsgReceivePulse failed!");
		 			exit(EXIT_FAILURE);
		 		}

		 		else {
		 			DispatchMessageToSubscriber(pulse.code, pulse.value.sival_int);
		 			printf("Dispatcher got Msg on pin %d, with %d\n",pulse.code, pulse.value.sival_int);
		 			// Sende Message weiter an alle subscriber
		 		}
		 			// Do not ignore OS pulses!
	 }

}

int Dispatcher::getConnectionID(){
	 return conIDDispatcher;
}




