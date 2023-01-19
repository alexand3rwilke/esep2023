/*
 * QnetServer.h
 *
 *  Created on: 15.12.2022
 *      Author: Dresske, Christian
 */

#ifndef SRC_MAIN_QNET_QNETSERVER_QNETSERVER_H_
#define SRC_MAIN_QNET_QNETSERVER_QNETSERVER_H_

#include "../../Dispatcher/Dispatcher.h"
#include "../../Logic/ContextData.h"

#define USE_GNS true
class QnetServer {
public:
	QnetServer(const char* attach_point, Dispatcher *disp, ContextData  *contextData);
	virtual ~QnetServer();
	int server();
	thread *ServerThread;
	Dispatcher *dispatcher;
	const char* attach_point;
	//Contextdata *data;
	int counter;
	ContextData  *contextData;
};

#endif /* SRC_QNET_QNETSERVER_QNETSERVER_H_ */
