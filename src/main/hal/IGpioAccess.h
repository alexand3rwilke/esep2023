/*
 * IGpioAccess.h
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */

#ifndef SRC_MAIN_HAL_IGPIOACCESS_H_
#define SRC_MAIN_HAL_IGPIOACCESS_H_

#include <stdint.h>

#include "GpioPorts.h"
#include "Registers.h"

class IGpioAccess {

public:
	IGpioAccess(void) {};
	virtual ~IGpioAccess(void) {};

	virtual bool readPin(EGpioPort, ERegister, uint8_t) = 0;
	virtual  void writePin(EGpioPort, ERegister, uint8_t, bool) = 0;
};

#endif /* SRC_MAIN_HAL_IGPIOACCESS_H_ */
