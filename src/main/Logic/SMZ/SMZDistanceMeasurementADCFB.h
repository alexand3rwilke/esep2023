/*
 * SMZDistanceMeasurement.h
 *
 *  Created on: 15.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZDISTANCEMEASUREMENTADCFB_H_
#define SRC_MAIN_LOGIC_SMZ_SMZDISTANCEMEASUREMENTADCFB_H_


#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "../../WSAData.h"
#include "SMZDistanceMeasurement_ADC_WS.h"
#include "../../Imports.h"

#include "../../hal/ADC_Service.h"
#include "../../ADC/ADC.h"
#include "../../ADC/TSCADC.h"

class SMZDistanceMeasurement_ADC_FB : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;
	WSAData *wsa_data;

public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
	ADC *adc;
};



#endif /* SRC_MAIN_LOGIC_SMZ_SMZDISTANCEMEASUREMENTADCFB_H_ */
