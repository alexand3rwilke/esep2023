/*
 * GpioControllerStub.h
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */

#ifndef SRC_TEST_HAL_GPIOCONTROLLERSTUB_H_
#define SRC_TEST_HAL_GPIOCONTROLLERSTUB_H_

#include "../../main/hal/IGpioAccess.h"

class GpioControllerStub : public IGpioAccess {

private:
	EGpioPort lastReadPortV;
	EGpioPort lastWrittenPortV;

	ERegister lastReadRegisterV;
	ERegister lastWrittenRegisterV;

	uint8_t lastReadPinV;
	uint8_t lastWrittenPinV;

	bool lastWrittenValueV;

public:
	GpioControllerStub();
	virtual ~GpioControllerStub();

	bool readPin(EGpioPort, ERegister, uint8_t) override;
	void writePin(EGpioPort, ERegister, uint8_t, bool) override;

	EGpioPort lastReadPort(void);
	EGpioPort lastWrittenPort(void);

	ERegister lastReadReg(void);
	ERegister lastWrittenReg(void);

	uint8_t lastReadPin(void);
	uint8_t lastWrittenPin(void);

	bool lastWrittenValue(void);
};

#endif /* SRC_TEST_HAL_GPIOCONTROLLERSTUB_H_ */
