/*
 * WSAData.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "WSAData.h"

WSAData::WSAData(Dispatcher *dispatcher){
	disp = dispatcher;
	dispID  = disp->getConnectionID();
}

WSAData::~WSAData(){

}



