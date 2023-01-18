/*
 * SMZwsBohrung.h
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZWSBOHRUNG_H_
#define SRC_MAIN_LOGIC_SMZ_SMZWSBOHRUNG_H_
#include "SMZ.h"

class SMZwsBohrung : Basestate{
public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_SMZ_SMZWSBOHRUNG_H_ */
