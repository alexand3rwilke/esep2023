/*
 * QnetClient.h
 *
 *  Created on: 19.12.2022
 *      Author: Dresske, Christian
 */

#ifndef SRC_MAIN_MQTTPUBLISH_MQTTPUBLISH_MQTTPUBLISH_H_
#define SRC_MAIN_MQTTPUBLISH_MQTTPUBLISH_MQTTPUBLISH_H_

#include "../dispatcher/Dispatcher.h"

#define USE_GNS true

class MQTTPublish {

public:
	MQTTPublish(Dispatcher *disp);
	virtual ~MQTTPublish();
	int client();
	thread *ClientThread;
	Dispatcher *dispatcher;
};

#endif /* SRC_MAIN_QNET_QNETCLIENT_QNETCLIENT_H_ */
