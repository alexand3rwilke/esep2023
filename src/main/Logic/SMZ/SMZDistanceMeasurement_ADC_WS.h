/*
 * SMZDistanceMeasurement_ADC_WS.h
 *
 *  Created on: 15.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZDISTANCEMEASUREMENT_ADC_WS_H_
#define SRC_MAIN_LOGIC_SMZ_SMZDISTANCEMEASUREMENT_ADC_WS_H_

#include "../Basestate.h"
#include "../RZ/RZ.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "../../WSAData.h"
#include "../Actions.h"
#include "../../Imports.h"
#include "../../ADC/ADC.h"


class SMZDistanceMeasurement_ADC_WS : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;
	double startZeit;
	double gesamtZeit;
	double endZeit;
	ADC *adc;
	WSAData *wsa_data;
	//TimerBZ* timerBZ;
	double zeit;
	void start_stopuhr();
	double stopp_stopuhr();
	bool warStartSchon;

public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};


#endif /* SRC_MAIN_LOGIC_SMZ_SMZDISTANCEMEASUREMENT_ADC_WS_H_ */

//class SMZDistanceMeasurement_ADC_WS : public Basestate{
//private:
//	int myChannel;
//	int myConnection;
//	Dispatcher *disp;
//	double time1, tstart;
//	ADC *adc;
//	WSAData *wsa_data;
//
//public:
//	void entry()override;
//	void exit() override;
//	void doAction(int, _pulse) override;
//};
//
//
//#endif /* SRC_MAIN_LOGIC_SMZ_SMZDISTANCEMEASUREMENT_ADC_WS_H_ */
