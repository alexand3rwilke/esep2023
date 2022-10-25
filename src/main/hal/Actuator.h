/*
 * Hardware.h
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */

#ifndef SRC_MAIN_HAL_HARDWARE_H_
#define SRC_MAIN_HAL_HARDWARE_H_

#include "IHardwareAbstraction.h"

#include "IGpioAccess.h"

class Hardware : public IHardwareAbstraction {

private:
	IGpioAccess* gpioController;

public:
	Hardware(IGpioAccess* gpioController);
	virtual ~Hardware();

	void assamblyMoveRightOn(void) override;
	void assamblyMoveRightOff(void) override;
	void assamblyMoveLeftOn(void) override;
	void assamblyMoveLeftOff(void) override;
	void assamblyMoveSlowOn(void) override;
	void assamblyMoveSlowOff(void) override;
	void assamblyStopOn(void) override;
	void assamblyStopOff(void) override;
	void redOn(void) override;
	void redOff(void) override;
	void yellowOn(void) override;
	void yellowOff(void) override;
	void greenOn(void) override;
	void greenOff(void) override;
	void switchOn(void) override;
	void switchOff(void) override;
};

#endif /* SRC_MAIN_HAL_HARDWARE_H_ */
