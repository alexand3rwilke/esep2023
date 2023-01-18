/*
 * ESZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_ESZ_H_
#define SRC_MAIN_LOGIC_ESZ_H_

#include "../Basestate.h"
#include "../../hal/Actuator.h"
#include "../Context.h"
#include "../RZ/RZ.h"
#include "../BZ/BZ.h"


class ESZ: public Basestate {
private:
	int resetCounter;
	bool schalter1Gedrueckt;
	bool schalter2Gedrueckt;

	bool estp1Finished;
	bool estp2Finished;

public:

	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_ESZ_H_ */
