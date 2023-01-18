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
#include "SMZTesting.h"
#include "../../WSAData.h"
#include "../../Imports.h"
#include "../ContextData.h"
#include "../Actions.h"
#include "SMZMesseGrundhoehe.h"
#include "SMZwsBohrung.h"
#include "SMZwsNormal.h"
#include "SMZwsMetall.h"
#include "SMZwsFlach.h"

class SMZ : public Basestate{
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

#endif /* SRC_MAIN_LOGIC_SMZ_H_ */
