/*
 * IHardwareAbstraction.h
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */
#ifndef SRC_MAIN_HAL_IHARDWAREABSTRACTION_H_
#define SRC_MAIN_HAL_IHARDWAREABSTRACTION_H_


class IHardwareAbstraction {

public:
	IHardwareAbstraction(void){};
	virtual ~IHardwareAbstraction(void){};

	virtual void assamblyMoveRightOn(void) = 0;
	virtual void assamblyMoveRightOff(void) = 0;
	virtual void assamblyMoveLeftOn(void) = 0;
	virtual void assamblyMoveLeftOff(void) = 0;
	virtual void assamblyMoveSlowOn(void) = 0;
	virtual void assamblyMoveSlowOff(void) = 0;
	virtual void assamblyStopOn(void) = 0;
	virtual void assamblyStopOff(void) = 0;
	virtual void redOn(void) = 0;
	virtual void redOff(void) = 0;
	virtual void yellowOn(void) = 0;
	virtual void yellowOff(void) = 0;
	virtual void greenOn(void) = 0;
	virtual void greenOff(void) = 0;
	virtual void switchOn(void) = 0;
	virtual void switchOff(void) = 0;
};


#endif /* SRC_MAIN_HAL_IHARDWAREABSTRACTION_H_ */
