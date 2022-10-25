/*
 * HardwareTest.h
 *
 *  Created on: 03.12.2021
 *      Author: Bjoern Dittmann
 */

#ifndef SRC_TEST_HAL_HARDWARETEST_H_
#define SRC_TEST_HAL_HARDWARETEST_H_

#include <gtest/gtest.h>
#include <iostream>

#include "../../main/hal/IHardwareAbstraction.h"
#include "../../main/hal/Hardware.h"
#include "GpioControllerStub.h"

using namespace std;

class HardwareTest: public ::testing::Test {

protected:
	IHardwareAbstraction* hw;
	GpioControllerStub* gpioAcc;

	virtual void SetUp() {
		this->gpioAcc = new GpioControllerStub();
		this->hw = new Hardware(this->gpioAcc);
	}

	virtual void TearDown() {
		delete this->hw;
		delete this->gpioAcc;
	}
};


TEST_F(HardwareTest, redOn_test){
	this->hw->redOn();

	EXPECT_EQ(
		EGpioPort::GPIO_PORT4,
		this->gpioAcc->lastWrittenPort()
	);

	EXPECT_EQ(
		ERegister::SETDATAOUT,
		this->gpioAcc->lastWrittenReg()
	);

	EXPECT_EQ(
		16,
		this->gpioAcc->lastWrittenPin()
	);

	EXPECT_EQ(
		true,
		this->gpioAcc->lastWrittenValue()
	);
};

TEST_F(HardwareTest, redOff_test){
	this->hw->redOff();

	EXPECT_EQ(
		EGpioPort::GPIO_PORT4,
		this->gpioAcc->lastWrittenPort()
	);

	EXPECT_EQ(
		ERegister::SETDATAOUT,
		this->gpioAcc->lastWrittenReg()
	);

	EXPECT_EQ(
		16,
		this->gpioAcc->lastWrittenPin()
	);

	EXPECT_EQ(
		false,
		this->gpioAcc->lastWrittenValue()
	);
};

TEST_F(HardwareTest, yellowOn_test){
	this->hw->yellowOn();

	EXPECT_EQ(
		EGpioPort::GPIO_PORT5,
		this->gpioAcc->lastWrittenPort()
	);

	EXPECT_EQ(
		ERegister::SETDATAOUT,
		this->gpioAcc->lastWrittenReg()
	);

	EXPECT_EQ(
		17,
		this->gpioAcc->lastWrittenPin()
	);

	EXPECT_EQ(
		true,
		this->gpioAcc->lastWrittenValue()
	);
};

TEST_F(HardwareTest, yellowOff_test){
	this->hw->yellowOff();

	EXPECT_EQ(
		EGpioPort::GPIO_PORT5,
		this->gpioAcc->lastWrittenPort()
	);

	EXPECT_EQ(
		ERegister::SETDATAOUT,
		this->gpioAcc->lastWrittenReg()
	);

	EXPECT_EQ(
		17,
		this->gpioAcc->lastWrittenPin()
	);

	EXPECT_EQ(
		true,		//Nehmen wir hier einen Copy-Paste Fehler an. Sollte eigentlich false sein!
		this->gpioAcc->lastWrittenValue()
	);
};

TEST_F(HardwareTest, greenOn_test){
	this->hw-> ();

	EXPECT_EQ(
		EGpioPort::GPIO_PORT6,
		this->gpioAcc->lastWrittenPort()
	);

	EXPECT_EQ(
		ERegister::SETDATAOUT,
		this->gpioAcc->lastWrittenReg()
	);

	EXPECT_EQ(
		18,
		this->gpioAcc->lastWrittenPin()
	);

	EXPECT_EQ(
		true,
		this->gpioAcc->lastWrittenValue()
	);
};

TEST_F(HardwareTest, greenOff_test){
	this->hw->greenOff();

	EXPECT_EQ(
		EGpioPort::GPIO_PORT6,
		this->gpioAcc->lastWrittenPort()
	);

	EXPECT_EQ(
		ERegister::SETDATAOUT,
		this->gpioAcc->lastWrittenReg()
	);

	EXPECT_EQ(
		18,
		this->gpioAcc->lastWrittenPin()
	);

	EXPECT_EQ(
		false,
		this->gpioAcc->lastWrittenValue()
	);
};

#endif /* SRC_TEST_HAL_HARDWARETEST_H_ */
