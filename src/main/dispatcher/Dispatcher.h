
/*
 * ADC.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke
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


class Dispatcher {
public:
	Dispatcher();
	void registerForEventWIthConnection(int event, int conI);
	int conIDDispatcher;

private:
	std::thread* DispThread;
	int chanID;
	void DispatchMessageToSubscriber(int8_t code, int value);
	void ListenForEvents();
};

#endif
