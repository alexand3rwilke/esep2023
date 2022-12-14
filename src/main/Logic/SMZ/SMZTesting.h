/*
 * SMZTesting.h
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_LOGIC_SMZ_SMZTESTING_H_
#define SRC_MAIN_LOGIC_SMZ_SMZTESTING_H_

#include "SMZ.h"

using namespace std;

class SMZTesting : public Basestate{
private:
	int myChannel;
	int myConnection;
	Dispatcher *disp;

public:
	void entry()override;
	void exit() override;
	void doAction() override;
};

#endif /* SRC_MAIN_LOGIC_SMZ_SMZTESTING_H_ */
