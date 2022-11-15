/*
 * Imports.h
 *
 *  Created on: 14.11.2022
 *      Author: acr819
 */

#ifndef SRC_IMPORTS_H_
#define SRCIMPORTS_H_

// Sensorik
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


/* Interrupt numbers  (spruh73l.pdf S.465 ff.) */
#define INTR_GPIO_PORT0 97
#define INTR_GPIO_PORT1 99
#define INTR_GPIO_PORT2 33


/* GPIO port addresses (spruh73l.pdf S.177 ff.) */
#define GPIO_PORT0 0x44E07000
#define GPIO_PORT1 0x4804C000
#define GPIO_PORT2 0x481AC000


/* GPIO port registers length */
#define GPIO_REGISTER_LENGHT 0x1000


/* GPIO register offsets (spruh73l.pdf S.4877) */
#define GPIO_LEVELDETECT0 0x140
#define GPIO_LEVELDETECT1 0x144
#define GPIO_RISINGDETECT 0x148
#define GPIO_FALLINGDETECT 0x14C

#define GPIO_IRQSTATUS_0 0x2C
#define GPIO_IRQSTATUS_1 0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38

#define GPIO_DATAIN 0x138
#define GPIO_SETDATAOUT 0x194


// Lichtschranken
#define LIGHTBARRIER_FRONT_PIN 2	//active low
#define LIGHTBARRIER_BACK_PIN 20
#define LIGHTBARRIER_SLIDE_PIN 15


//Buttons
#define BUTTON_START_PIN 22			//active high
#define BUTTON_STOP_PIN 23
#define BUTTON_RESET_PIN 26
#define BUTTON_ESTOP_PIN 27

//Metall Detector
#define METALL_DET_PIN 7

#define ADC_DONE 21
