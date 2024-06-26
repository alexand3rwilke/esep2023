/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZEinlauf.h"
#include "BZHoehenmessung.h"
#include "../Actions.h"




void BZEinlauf::entry() {
	cout << "\n  BZEinlauf entry\n" << endl;
	if(FESTO_TYPE == 1 && contextData->isLse1Free()){
		actions->startFB();
	} else if (FESTO_TYPE == 2){
		actions->startFB();
	}

	if(FESTO_TYPE==1){
		stateTimer = new SimpleTimer(this->contextData->disp);
		stateTimer->startTimer();
	}
	//TimerBZ *timerBz = new TimerBZ(contextData->disp,10,-1, STATE_TOO_LONG);




}
    void BZEinlauf::exit() {

		if(FESTO_TYPE==1){
				stateTimer->stopTimer();
				stateTimer->resetTimer();
		}
    }
    void BZEinlauf::estp() {


    }
    void BZEinlauf::doAction(int event, _pulse msg){



    		switch (event) {

    		case ADC_WK_IN_HM :
				if(FESTO_TYPE==1){
    			if(stateTimer->getTime() > 2) {
    			exit();
    			new(this) BZHoehenmessung;
    			entry();

    			}
				}else {
					exit();
    				new(this) BZHoehenmessung;
    				entry();
				}

    			break;

    		}

    	}
