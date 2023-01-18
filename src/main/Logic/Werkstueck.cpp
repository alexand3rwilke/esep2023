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


Werkstueck::Werkstueck(string wkJson) {

	    size_t pos = wkJson.find("werkstueckTyp") + 15;
	    size_t end = wkJson.find(",", pos);
	    werkstueckTyp = std::stoi(wkJson.substr(pos, end - pos));

	    pos = wkJson.find("absoluteHoehe") + 14;
	    end = wkJson.find(",", pos);
	    absoluteHoehe = std::stoi(wkJson.substr(pos, end - pos));

	    pos = wkJson.find("mittlereHoehe") + 15;
	    end = wkJson.find(",", pos);
	    mittlereHoehe = std::stoi(wkJson.substr(pos, end - pos));

	    pos = wkJson.find("wkFlipped") + 11;
	    end = wkJson.find(",", pos);
	    wkFlipped = wkJson.substr(pos, end - pos) == "true";

	    pos = wkJson.find("aussortieren") + 13;
	    end = wkJson.find("}", pos);
	    aussortieren = wkJson.substr(pos, end - pos) == "true";
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

string Werkstueck::toJsonString() {

	stringstream json_stream;
	json_stream << "{";
	json_stream << "\"werkstueckTyp\":" << to_string(werkstueckTyp) << ",";
	json_stream << "\"absoluteHoehe\":" << to_string(absoluteHoehe) << ",";
	json_stream << "\"mittlereHoehe\":" << to_string(mittlereHoehe) << ",";
	json_stream << "\"wkFlipped\":" << (wkFlipped ? "true" : "false") << ",";
	json_stream << "\"aussortieren\":" << (aussortieren ? "true" : "false");
	return json_stream.str();
	}

