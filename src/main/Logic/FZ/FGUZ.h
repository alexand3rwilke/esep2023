/*
 * FGUZ.h
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_FZ_FGUZ_H_
#define SRC_MAIN_LOGIC_FZ_FGUZ_H_
#include "FZ.h"

class FGUZ: public Basestate {
public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_FZ_FGUZ_H_ */
