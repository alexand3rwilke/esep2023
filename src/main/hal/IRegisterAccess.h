/*
 * IRegisterAccess.h
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */

#ifndef SRC_MAIN_HAL_IREGISTERACCESS_H_
#define SRC_MAIN_HAL_IREGISTERACCESS_H_

#include <stdint.h>

class IRegisterAccess {

	IRegisterAccess(void) {};
	virtual ~IRegisterAccess(void) {};

	int readRegister(uintptr_t) = 0;
	void writeRegister(uintptr_t, uint32_t) = 0;
};


#endif /* SRC_MAIN_HAL_IREGISTERACCESS_H_ */
