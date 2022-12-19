/*
 * BZready.cpp
 *
 *  Created on: 05.12.2022
 *      Author: Hendrik Marquardt
 */

#include "BZHoehenmessung.h"
#include "BZAussortierer.h"



void BZHoehenmessung::entry() {

	cout << "\n  BZHoehenmessung entry\n" << endl;
	actions->moveSlower();

}
    void BZHoehenmessung::exit() {
    	actions->moveFaster();
    }
    void BZHoehenmessung::estp() {


    }
    void BZHoehenmessung::doAction(int event, _pulse msg){




		switch (event) {



		case ADC_WK_NIN_HM :
			exit();
			new(this) BZAussortierer;
			entry();
			break;

		}


    }
