/*
 * SMZCalibration.h
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZCALIBRATION_H_
#define SRC_MAIN_LOGIC_SMZ_SMZCALIBRATION_H_

#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "../../WSAData.h"
#include "SMZDistanceMeasurementADCFB.h"
#include "../../Imports.h"

#include "../RZ/RZ.h"
#include "../BZ/BZ.h"



class SMZCalibration : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;
	Actuator *act;
	WSAData *wsa_data;

public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;

	void clearThresholds(void);
	int distanceMeasurementFB(void);
	int distanceMeasurementWS(void);
	int determineSorter(void);
};



#endif /* SRC_MAIN_LOGIC_SMZ_SMZCALIBRATION_H_ */
