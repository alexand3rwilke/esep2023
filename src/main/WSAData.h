/*
 * WSAData.h
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_WSADATA_H_
#define SRC_MAIN_WSADATA_H_

#include "dispatcher/Dispatcher.h"

/**
 * Daten zur WSA
 */
class WSAData{
public:
	WSAData();
	virtual~WSAData();

	int sorterTyp;
	int distance_FB_ADC;
	int distance_FWS_ADC;
	int distance_WS_ADC;

	int distance_LSA_ADC;
	int distance_ADC_LSS;
	int distance_LSS_LSE;
};

#endif /* SRC_MAIN_WSADATA_H_ */
