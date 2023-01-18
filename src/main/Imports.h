/*
 * Imports.h
 *
 *  Created on: 14.11.2022
 *      Author: acr819, Marquahe
 */

//Includes
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <sys/procmgr.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <thread>
#include <vector>
#include <list>
#include <map>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <mutex>
#include <ctime>
#include <time.h>


using namespace std;

#ifndef SRC_IMPORTS_H_
#define SRC_IMPORTS_H_


// which FA am I?
extern int FESTO_TYPE;
/*------------------------Pins--------------------------*/

// Sensorik
#define GPIO2_ADDRESS_START (uint64_t)0x481AC000
#define GPIO_REGISTER_LENGHT 0x1000
#define GPIO_DATAIN 0x138

// ADC Stuff
#define ADC_BASE 0x44E0D000
#define ADC_LENGTH 0x2000
#define ADC_DATA 0x100
#define ADC_DONE 21

#define GPIO0_ADDRESS_START (uint64_t) 0x44E07000

//Aktuator
#define GPIO1_ADDRESS_START (uint64_t)0x4804C000
#define GPIO1_ADDRESS_LENGTH 0x1000
#define GPIO_SET_REGISTER(base) (uintptr_t)base + 0x194
#define GPIO_CLEAR_REGISTER(base) (uintptr_t)base + 0x190

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
#define LSA 2	//active low
#define LSE 20
#define LSR 15
#define LSS 5
#define HMS 3

//Buttons
#define STR 22			//active high
#define STP 23
#define RST 26
#define ESTP 27

//LEDs pin

//Metall Detector
#define MTD 7

//Rampe


/* ------------------------Aktionen ------------------------*/

//Aktionen der Aktorik
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
#define GREEN_BLINKING_ON 60
#define YELLOW_BLINKING_ON 61
#define RED_BLINKING_ON 62
#define AMP_ALL_OFF 63

//Aktionen der Sensorik

// FESTO 1 Sensor Interrupt
#define LSA1interrupted 100
#define LSA1notInterrupted 101
#define LSS1interrupted 102
#define LSS1notInterrupted 103
#define LSR1interrupted 104
#define LSR1notInterrupted 105
#define LSE1interrupted 106
#define LSE1notInterrupted 107
#define MTD1interrupted 99

// FESTO 2 Sensor interrupt
#define LSA2interrupted 40
#define LSE2interrupted 41
#define LSE2notInterrupted 42

#define LSR2interrupted 43
#define LSR2notInterrupted 44

//Aktion ADC
#define HMSinterrupted 108
#define ADC_SAMLING_FINISHED 120
#define ADC_START_SAMPLE 121
#define ADC_SAMPLE_VALUE 122
#define ADC_WK_IN_HM 123
#define ADC_WK_NIN_HM 124
#define ADC_SAMLING__VALUE_FINISHED 125
#define ADC_SINGLE_SAMLING_FINISHED 126
#define ADC_START_SINGLE_SAMPLE 127

//Aktionen der Buttons
#define STRinterrupted 109
#define STRnotInterrupted 110
#define STPinterrupted 111
//#define STPnotInterrupted 112
#define RSTinterrupted 112
//#define RSTnotInterrupted 114
#define ESTP1interrupted 114
#define ESTP1notInterrupted 115
#define STR_SMZ 120


// FESTO 2 ESTP
#define ESTP2interrupted 80
#define ESTP2notInterrupted 81

//Aktionen der LED
#define Q1On 98
#define Q1Off 97
#define Q2On 96
#define Q2Off 95

//Aktionen alles weitere
#define ACTIVTE_AUSSORTIERER 116
#define TimerTimeout 117
#define WS_AUSSORTIEREN 119
#define WS_DURCHLASSEN 118

//enum WS{FWS, WSMB, WSMM, WSO}

#define HELLO 125
extern int MIN_HOEHE;
extern int MAX_HOEHE;


#define WK_FLACH 35
#define WK_Normal 36
#define WK_Bohrung_Metal 37
#define WK_Bohrung_Normal 38
#define WK_UNDEFINED 39


//
#define WK_REMOVED 70
#define WK_ADDED 71


#define TIMER_IS_OVER 89
#define SMZ_CHECK_HOEHE 46
#define START_SMZ 47

#define ESTP1Finished 90
#define ESTP2Finished 91

#define WK_ON_FB2 92
#define WK_NON_FB2 93


#define RUTSCHE_1_VOLL 29
#define RUTSCHE_2_VOLL 30

#define RUTSCHE_1_LEER 31
#define RUTSCHE_2_LEER 32

#define STATE_TOO_LONG 34

#define FA2_RUNNING 67
#define FA2_STOPPED 68

#define WK_TELEPORT 94


enum WkType { WKN,WKF,WKB,WKBM,WKU,NOWK};


#endif /* SRC_IMPORTS_H */
