/*
 * Imports.h
 *
 *  Created on: 14.11.2022
 *      Author: acr819
 */

#ifndef SRC_IMPORTS_H_
#define SRCIMPORTS_H_

// Sensorik
#define GPIO2_ADDRESS_START (uint64_t)0x481AC000
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

#define ADC_SAMLING_FINISHED 120
#define ADC_START_SAMPLE 121
#define ADC_SAMPLE_VALUE 122
#define ADC_WK_IN_HM 123
#define ADC_WK_NIN_HM 124




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
#define LSA1 2	//active low
#define LSE1 20
#define LSR1 15
#define LSS1 5
#define HMS1 3


//Buttons
#define SRT 22			//active high
#define STP 23
#define RST 26
#define ESTP 27

//LEDs pin


//Metall Detector
#define MTD1 7

#define ADC_DONE 21

//Die aktion die die Aktorik durchführen soll
#define START_FB 50
#define STOP_FB 51
#define MOVE_FASTER 52
#define MOVE_SLOWER 53
#define GREEN_ON 54
#define GREEN_OFF 55
#define YELLOW_ON 56
#define YELLOW_OFF 57
#define RED_ON 58
#define RED_OFF 59


//Sensorik
#define LSAinterrupted 100
#define LSAnotInterrupted 101
#define LSSinterrupted 102
#define LSSnotInterrupted 103
#define LSRinterrupted 104
#define LSRnotInterrupted 105
#define LSEinterrupted 106
#define LSEnotInterrupted 107

#define HMSinterrupted 108

#define STRinterrupted 109
#define STRnotInterrupted 110
#define STPinterrupted 111
//#define STPnotInterrupted 112
#define RSTinterrupted 113
//#define RSTnotInterrupted 114
#define ESTPinterrupted 115
#define ESTPnotInterrupted 116

#define ACTIVTE_AUSSORTIERER 117



