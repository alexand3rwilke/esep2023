/*
 * BasicState.h
 *
 *  Created on: 30.11.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_LOGIC_BASICSTATE_H_
#define SRC_MAIN_LOGIC_BASICSTATE_H_

class BasicState {
public:
	virtual ~BasicState(){
	};
	virtual void entry() = 0;
	virtual void exit() = 0;
	virtual void estp() = 0;
	virtual void doAction() = 0;
	//
};



#endif /* SRC_MAIN_LOGIC_BASICSTATE_H_ */
