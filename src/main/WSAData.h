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

	//Gibt an, welche FBM dieses Program ausführt
	bool fbm1;
	bool fbm2;

	void setSorterTyp(int);
	void setDistance_FB_ADC(int);
	void setDistance_FWS_ADC(int);
	void setDistance_WS_ADC(int);
	void setDistance_LSA_ADC(int);
	void setDistance_ADC_LSS(int);
	void setDistance_LSS_LSE(int);
	void setFBM1(bool);
	void setFBM2(bool);

	int getSorterTyp(void);
	int getDistance_FB_ADC(void);
	int getDistance_FWS_ADC(void);
	int getDistance_WS_ADC(void);
	int getDistance_LSA_ADC(void);
	int getDistance_ADC_LSS(void);
	int getDistance_LSS_LSE(void);
	bool getFBM(void);
};

#endif /* SRC_MAIN_WSADATA_H_ */
