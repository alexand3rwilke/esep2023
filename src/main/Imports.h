/*
 * Imports.h
 *
 *  Created on: 14.11.2022
 *      Author: acr819
 */

#ifndef SRC_IMPORTS_H_
#define SRCIMPORTS_H_

// Sensorik
#define GPIO_PORT0 (uint64_t)0x44E07000
#define GPIO_REGISTER_LENGHT 0x1000
#define GPIO_DATAIN 0x138

// ADC Stuff
#define ADC_BASE 0x44E0D000
#define ADC_LENGTH 0x2000
#define ADC_DATA 0x100

//Aktuator
#define GPIO1_ADDRESS_START (uint64_t)0x4804C000
#define GPIO1_ADDRESS_LENGTH 0x1000
#define GPIO_SET_REGISTER(base) (uintptr_t)base + 0x194
#define GPIO_CLEAR_REGISTER(base) (uintptr_t)base + 0x190

#endif /* SRCIMPORTS_H_ */
