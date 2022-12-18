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

class ESZ: public Basestate {
private:

public:

	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_ESZ_H_ */
