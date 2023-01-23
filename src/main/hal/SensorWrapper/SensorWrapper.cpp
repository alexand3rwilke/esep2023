/*
 * SensorWrapper.cpp
 *
 *  Created on: 6 Jan 2023
 *      Author: Alexander Wilke
 */

#include "SensorWrapper.h"
#include "../../Imports.h"

SensorWrapper::SensorWrapper() {


}

SensorWrapper::~SensorWrapper() {

}



int SensorWrapper::readPin(uint32_t bank, uint32_t bit){
	 int value = in32((uintptr_t) (bank + GPIO_DATAIN));
	 value = value & (1<<bit);
	 return value;
}

