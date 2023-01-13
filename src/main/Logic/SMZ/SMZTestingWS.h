/*
 * SMZTestingWS.h
 *
 *  Created on: 18.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZTESTINGWS_H_
#define SRC_MAIN_LOGIC_SMZ_SMZTESTINGWS_H_

#include "SMZ.h"
#include "../RZ/RZ.h"
#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "../../WSAData.h"
#include "../../Imports.h"

class SMZTestingWS : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;
	bool wkTest;
	WSAData *wsa_data;

public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_SMZ_SMZTESTINGWS_H_ */
