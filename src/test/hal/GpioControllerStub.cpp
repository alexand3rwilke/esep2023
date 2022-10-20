/*
 * GpioControllerStub.cpp
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */

#include "GpioControllerStub.h"

GpioControllerStub::GpioControllerStub() {}

GpioControllerStub::~GpioControllerStub() {}

bool GpioControllerStub::readPin(EGpioPort port, ERegister reg, uint8_t pin) {
	this->lastReadPortV = port;
	this->lastReadRegisterV = reg;
	this->lastReadPinV = pin;

	return false;	//manage gpio state here
}

void GpioControllerStub::writePin(EGpioPort port, ERegister reg, uint8_t pin,
		bool val) {
	this->lastWrittenPortV = port;
	this->lastWrittenRegisterV = reg;
	this->lastWrittenPinV = pin;
	this->lastWrittenValueV = val;
}

EGpioPort GpioControllerStub::lastReadPort(void) {
	return this->lastReadPortV;
}

EGpioPort GpioControllerStub::lastWrittenPort(void) {
	return this->lastWrittenPortV;
}

ERegister GpioControllerStub::lastReadReg(void) {
	return this->lastReadRegisterV;
}

ERegister GpioControllerStub::lastWrittenReg(void) {
	return this->lastWrittenRegisterV;
}

uint8_t GpioControllerStub::lastReadPin(void) {
	return this->lastReadPinV;
}

uint8_t GpioControllerStub::lastWrittenPin(void) {
	return this->lastWrittenPinV;
}

bool GpioControllerStub::lastWrittenValue(void) {
	return this->lastWrittenValueV;
}

