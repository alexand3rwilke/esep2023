
/*
 * ADC.ch
 *
 *  Created on: 25.10.22
 *      Author: Alexander Wilke, Marquahe
 */

#include "../Imports.h"

#ifndef SRC_MAIN_HAL_ADC_H_
#define SRC_MAIN_HAL_ADC_H_

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
	std::mutex connectionMutex;
	std::map<int8_t, vector<int>> connectionMap;
	void DispatchMessageToSubscriber(int8_t code, int value);
	void ListenForEvents();
	int conIDDispatcher;

};

#endif
