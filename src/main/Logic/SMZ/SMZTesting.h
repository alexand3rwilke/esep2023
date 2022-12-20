/*
 * SMZTesting.h
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZTESTING_H_
#define SRC_MAIN_LOGIC_SMZ_SMZTESTING_H_

#include "SMZ.h"
#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "../../WSAData.h"
#include "../../Imports.h"
#include "SMZTestingWS.h"

class SMZTesting : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;
	WSAData *wsa_data;

public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_SMZ_SMZTESTING_H_ */
