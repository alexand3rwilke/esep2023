/*
 * FZ.h
 *
 *  Created on: 30.11.2022
 *      Author: Marquahe
 */

#ifndef SRC_MAIN_LOGIC_FZ_H_
#define SRC_MAIN_LOGIC_FZ_H_

#include "../ContextData.h"
#include "../../Imports.h"
#include "../Actions.h"
#include "../Basestate.h"
#include "../Context.h"
#include "../BZ/BZ.h"
#include "../ESZ/ESZ.h"
#include "FGUZ.h"
#include "FAUZ.h"
#include "FAQZ.h"
#include "../TimerBZ.h"


class FZ: public Basestate {
private:
	Basestate *substate;

public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};
#endif /* SRC_MAIN_LOGIC_FZ_H_ */

