/*
 * SMZwsMetall.h
 *
 *  Created on: 18.01.2023
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZWSMETALL_H_
#define SRC_MAIN_LOGIC_SMZ_SMZWSMETALL_H_

#include "SMZ.h"
class SMZwsMetall : Basestate{
public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_SMZ_SMZWSMETALL_H_ */
