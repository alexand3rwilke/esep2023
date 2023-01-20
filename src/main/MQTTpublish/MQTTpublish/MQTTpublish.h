/*
 * QnetClient.h
 *
 *  Created on: 19.12.2022
 *      Author: Dresske, Christian
 */

#ifndef SRC_MAIN_MQTTPUBLISH_MQTTPUBLISH_MQTTPUBLISH_H_
#define SRC_MAIN_MQTTPUBLISH_MQTTPUBLISH_MQTTPUBLISH_H_

#include "../../dispatcher/Dispatcher.h"
#include "../../Logic/ContextData.h"

using namespace std;

#define USE_GNS true

class MQTTPublish {
private:
	ContextData *contextData;
	string ergebnisString = " ";


public:
	MQTTPublish(Dispatcher *disp, ContextData *contextData);
	virtual ~MQTTPublish();
	void client(void);

//	void setErgebnisString( string ergebnisString) {
//		this->ergebnisString = ergebnisString;
//	}
	void sendToConsole(string wert);

	thread *ClientThread;
	Dispatcher *dispatcher;
};

#endif /* SRC_MAIN_QNET_QNETCLIENT_QNETCLIENT_H_ */
