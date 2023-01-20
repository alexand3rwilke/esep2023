/*
 * Werkstueck.h
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_WERKSTUECK_H_
#define SRC_MAIN_WERKSTUECK_H_
#include "../Imports.h"
#include <sstream>


/**
 *
 */
class Werkstueck{
public:
	Werkstueck();
	Werkstueck(string wkJson);
	virtual~Werkstueck();

	int werkstueckTyp;
	int absoluteHoehe;
	int mittlereHoehe;
	bool wkFlipped;
	bool aussortieren;

	int getWkType(void);
	void setWkType(int wkType);

	int getAbsoluteHoehe(void);
	void setAbsoluteHoehe(int absoluteHoehe);

	int getMittlereHoehe(void);
	void setMittlereHoehe(int mittlereHoehe);

	bool getWkFlipped(void);
	void setWkFlipped(bool wkFlipped);

	bool getAussortieren(void);
	void setAussortieren(bool aussortieren);

	string toJsonString(void);
	string toString(void);


};

#endif /* SRC_MAIN_WERKSTUECK_H_ */
