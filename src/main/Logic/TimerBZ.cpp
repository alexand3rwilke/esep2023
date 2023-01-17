/*
 * TimerBZ.cpp
 *
 *  Created on: 21.12.2022
 *      Author: Jobut
 */

#include "TimerBZ.h"


TimerBZ::TimerBZ() {

}

TimerBZ::TimerBZ(Dispatcher *disp, int seconds, int event, int reactionEvent) {
	this->seconds = seconds;
	this->event = event;
	this->reactionEvent = reactionEvent;
	this->disp = disp;
	dispConID = disp->getConnectionID();
	timer = new std::thread([this]() {setUp();});
	chanKeeper = new std::thread([this]() {timerGestartet();});
}

TimerBZ::~TimerBZ() {
	// TODO Auto-generated destructor stub
}


void TimerBZ::setUp(){

	int chanID = ChannelCreate(0);
			if (chanID < 0) {
				perror("Could not create a channel!\n");
			}


			int conID = ConnectAttach(0, 0, chanID, _NTO_SIDE_CHANNEL, 0);
			if (conID < 0) {
				perror("Could not connect to channel!");
			}
			std::vector<int8_t> events = {event};
			disp->registerForEventWIthConnection(events, conID);
			_pulse pulse;


				int recvid = MsgReceivePulse(chanID, &pulse, sizeof(_pulse), nullptr);

				if (recvid < 0) {
						perror("MsgReceivePulse failed!- in Timer");
						exit(EXIT_FAILURE);
				}

				recivedIntereupt = true;
				cout << "Timer ---------------------------- gut" << endl;



}

void TimerBZ::timerGestartet(){
	usleep(1000 * (seconds * 1000 ));
	if(!recivedIntereupt){
		cout << "Timer Fehler" << endl;
		MsgSendPulse(dispConID,-1,this->reactionEvent,0);
	}
}

void TimerBZ::startTimer(){
	start_time = time(NULL);
}

void TimerBZ::stopTimer(){

	end_time = time(NULL);
	double timerResult = difftime(end_time,start_time);
	cout << timerResult << endl;

}
