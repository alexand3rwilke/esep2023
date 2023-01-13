/*
 * QnetClient.h
 *
 *  Created on:
 *      Author:
 */

#ifndef SRC_MAIN_QNET_QNETCLIENT_QNETCLIENT_H_
#define SRC_MAIN_QNET_QNETCLIENT_QNETCLIENT_H_

#include "../../dispatcher/Dispatcher.h"

#define USE_GNS true

class QnetClient {

public:
	QnetClient(const char* attach_point, Dispatcher *disp);
	virtual ~QnetClient();
	int client();
	thread *ClientThread;
	Dispatcher *dispatcher;
	const char* attach_point;
	int counter;
	//Contextdata *data;
};

#endif /* SRC_MAIN_QNET_QNETCLIENT_QNETCLIENT_H_ */
