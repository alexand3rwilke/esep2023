/*
 * WarteAufFlachesWS.h
 *
 *  Created on: 16.01.2023
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZWSFLACH_H_
#define SRC_MAIN_LOGIC_SMZ_SMZWSFLACH_H_

#include "../../Imports.h"
#include "SMZ.h"

class SMZwsFlach : public Basestate{
private:

public:
	void entry()override;
	void exit() override;
	void doAction(int, _pulse) override;
};

#endif /* SRC_MAIN_LOGIC_SMZ_SMZWSFLACH_H_ */
