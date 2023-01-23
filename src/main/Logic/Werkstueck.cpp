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

	 // extract the values from the JSON string and assign them to the class' member variables

	std::vector<std::string> substrings;
	    std::size_t start = 0, end = 0;
	    string delimiter= " ";
	    while ((end = wkJson.find(delimiter, start)) != std::string::npos) {
	        substrings.push_back(wkJson.substr(start, end - start));
	        start = end + delimiter.length();
	    }
	    substrings.push_back(wkJson.substr(start));


	    	werkstueckTyp = stoi(substrings.at(0));
	    	absoluteHoehe = stoi(substrings.at(1));
	    	mittlereHoehe = stoi(substrings.at(2));
	    	wkFlipped = substrings.at(3) == "true";
	    	aussortieren = substrings.at(4) == "true";


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

	string Werkstueck::toString() {

		stringstream json_stream;
			json_stream << to_string(werkstueckTyp) << " ";
			json_stream << to_string(absoluteHoehe) << " ";
			json_stream << to_string(mittlereHoehe) << " ";
			json_stream << (wkFlipped ? "true" : "false") << " ";
			json_stream << (aussortieren ? "true" : "false");

			return json_stream.str();
	}

string Werkstueck::toJsonString() {

	stringstream json_stream;
	json_stream << "{";

	switch(werkstueckTyp) {

	case WK_Normal:
		json_stream << "\"werkstueckTyp\":" << "Normal" << ",";
		break;

	case WK_FLACH:
		json_stream << "\"werkstueckTyp\":" << "Flach" << ",";
		break;

	case WK_Bohrung:
		json_stream << "\"werkstueckTyp\":" << "Bohrung" << ",";
		break;

	case WK_Bohrung_Metal:
		json_stream << "\"werkstueckTyp\":" << "Bohrung Metall" << ",";
		break;

	case WK_UNDEFINED:
		json_stream << "\"werkstueckTyp\":" << "Undefined" << ",";
		break;

	default :
		json_stream << "\"werkstueckTyp\":" << "Undefined" << ",";
		break;



	}
	json_stream << "\"absoluteHoehe\":" << to_string(absoluteHoehe) << ",";
	json_stream << "\"mittlereHoehe\":" << to_string(mittlereHoehe) << ",";
	json_stream << "\"wkFlipped\":" << (wkFlipped ? "true" : "false") << ",";
	json_stream << "\"aussortieren\":" << (aussortieren ? "true" : "false");
	json_stream << "}";
	return json_stream.str();
	}

