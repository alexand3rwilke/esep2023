/*
 * BZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut, Marquahe
 */

#ifndef SRC_MAIN_LOGIC_BZ_BZ_H_
#define SRC_MAIN_LOGIC_BZ_BZ_H_

#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "../../WSAData.h"
#include "../ESZ/ESZ.h"
#include "BZready.h"
#include "BZEinlauf.h"
#include "BZAuslauf.h"
#include "BZAussortierer.h"
#include "BZHoehenmessung.h"
#include "../FZ/FZ.h"






/**
 * Erbt von Basic_State
 */
class BZ : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;


public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_BZ_H_ */
