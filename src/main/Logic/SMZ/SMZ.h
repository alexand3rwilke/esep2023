/*
 * SMZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_SMZ_H_
#define SRC_MAIN_LOGIC_SMZ_H_

#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "SMZCalibration.h"
#include "SMZTesting.h"
#include "../../WSAData.h"
#include "../../Imports.h"

class SMZ : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;

public:
	void entry()override;
	void exit() override;
	void doAction(int) override;
};

#endif /* SRC_MAIN_LOGIC_SMZ_H_ */
