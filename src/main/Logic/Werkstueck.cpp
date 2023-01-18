/*
 * Werkstueck.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "Werkstueck.h"

Werkstueck::Werkstueck() {
	werkstueckTyp = 0;
	absoluteHoehe = 0;
	mittlereHoehe = 0;
	wkFlipped = false;
	aussortieren = false;

}

Werkstueck::~Werkstueck(){

}

int Werkstueck::getWkType() {
return werkstueckTyp;

}
void Werkstueck::setWkType(int wkType) {
	this->werkstueckTyp = wkType;

}
int Werkstueck::getAbsoluteHoehe() {

return absoluteHoehe;

	}
	void Werkstueck::setAbsoluteHoehe(int absoluteHoehe) {

		this->absoluteHoehe = absoluteHoehe;
	}

	int Werkstueck::getMittlereHoehe() {
return mittlereHoehe;

	}
	void Werkstueck::setMittlereHoehe(int mittlereHoehe) {
		this->mittlereHoehe = mittlereHoehe;

	}

bool Werkstueck::getWkFlipped() {

	return wkFlipped;

	}
void Werkstueck::setWkFlipped(bool wkFlipped) {
	this->wkFlipped = wkFlipped;

	}

	bool Werkstueck::getAussortieren() {

return aussortieren;
	}
	void Werkstueck::setAussortieren(bool aussortieren) {

this->aussortieren = aussortieren;
	}

