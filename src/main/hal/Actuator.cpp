/*
 * Hardware.cpp
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */

#include "Hardware.h"

#include "GpioPorts.h"
#include "Registers.h"

Hardware::Hardware(IGpioAccess* gpioController) {
	this->gpioController = gpioController;
}

Hardware::~Hardware() {

}

// ASSAMBLY LINE
void Hardware::assamblyMoveRightOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT0,
		ERegister::SETDATAOUT,
		12,
		true
	);
}

void Hardware::assamblyMoveRightOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT0,
		ERegister::SETDATAOUT,
		12,
		false
	);
}

void Hardware::assamblyMoveLeftOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT1,
		ERegister::SETDATAOUT,
		13,
		true
	);
}

void Hardware::assamblyMoveLeftOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT1,
		ERegister::SETDATAOUT,
		13,
		false
	);
}

void Hardware::assamblyMoveSlowOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT2,
		ERegister::SETDATAOUT,
		14,
		true
	);
}

void Hardware::assamblyMoveSlowOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT2,
		ERegister::SETDATAOUT,
		14,
		false
	);
}


void Hardware::assamblyStopOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT3,
		ERegister::SETDATAOUT,
		15,
		true
	);
}

void Hardware::assamblyStopOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT3,
		ERegister::SETDATAOUT,
		15,
		false
	);
}


void Hardware::redOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT4,
		ERegister::SETDATAOUT,
		16,
		true
	);
}

void Hardware::redOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT4,
		ERegister::SETDATAOUT,
		16,
		false
	);
}

void Hardware::yellowOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT5,
		ERegister::SETDATAOUT,
		17,
		true
	);
}

void Hardware::yellowOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT5,
		ERegister::SETDATAOUT,
		17,
		false
	);
}

void Hardware::greenOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT6,
		ERegister::SETDATAOUT,
		18,
		true
	);
}

void Hardware::greenOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT6,
		ERegister::SETDATAOUT,
		18,
		false
	);
}


//SWITCH
void Hardware::switchOn(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT7,
		ERegister::SETDATAOUT,
		19,
		true
	);
}

void Hardware::switchOff(void) {
	this->gpioController->writePin(
		EGpioPort::GPIO_PORT7,
		ERegister::SETDATAOUT,
		19,
		false
	);
}










