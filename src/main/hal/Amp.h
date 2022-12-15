/*
 * Amp.h
 *
 *  Created on: 15.12.2022
 *      Author: Jobut
 */

#ifndef SRC_MAIN_HAL_AMP_H_
#define SRC_MAIN_HAL_AMP_H_

//#include "Actuator.h"
#include "../Imports.h"
using namespace std;

enum Farbe {
    GRUEN, GELB, ROT,
};

class Amp {
private:

	uintptr_t gpio_bank_1;


	std::thread* Rot_BlinkenT;
	std::thread* Gelb_BlinkenT;
	std::thread* Gruen_BlinkenT;
	bool redIsFlashing;
	bool yellowIsFlashing;
	bool greenIsFlashing;

	void StartRotBlinken(int);
	void StartGelbBlinken(int);
	void StartGruenBlinken(int);
public:
	Amp();
	virtual ~Amp();
	void ampOff(void);

	void redOn(void);
	void redOff(void);
	void yellowOn(void);
	void yellowOff(void);
	void greenOn(void);
	void greenOff(void);
	void greenBlinken(int);


	 void Ampel_Blinken(Farbe, int);
};


#endif /* SRC_MAIN_HAL_AMP_H_ */
