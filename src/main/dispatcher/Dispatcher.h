
/*
 * ADC.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke, Marquahe
 */


#ifndef SRC_MAIN_HAL_ADC_H_
#define SRC_MAIN_HAL_ADC_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <sys/procmgr.h>
#include <unistd.h>
#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <thread>
#include <vector>
#include<map>
#include<list>


class Dispatcher {
public:
	Dispatcher();
	virtual ~Dispatcher();
	void registerForEventWIthConnection(std::vector<int8_t> events, int conID);
	int getConnectionID();

private:
	std::thread* DispThread;
	int chanID;
	std::vector<int> connections;
	void DispatchMessageToSubscriber(int8_t code, int value);
	void ListenForEvents();
	int conIDDispatcher;

};

#endif
