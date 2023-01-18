/*
 * Werkstueck.h
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#ifndef SRC_MAIN_WERKSTUECK_H_
#define SRC_MAIN_WERKSTUECK_H_
#include "../Imports.h"


/**
 *
 */
class Werkstueck{
public:
	Werkstueck();
	virtual~Werkstueck();

	WkType werkstueckTyp;
	int absoluteHoehe;
	int mittlereHoehe;
	bool wkFlipped;
	bool aussortieren;

	WkType getWkType(void);
	void setWkType(WkType wkType);

	int getAbsoluteHoehe(void);
	void setAbsoluteHoehe(int absoluteHoehe);

	int getMittlereHoehe(void);
	void setMittlereHoehe(int mittlereHoehe);

	bool getWkFlipped(void);
	void setWkFlipped(bool wkFlipped);

	bool getAussortieren(void);
	void setAussortieren(bool aussortieren);

};

#endif /* SRC_MAIN_WERKSTUECK_H_ */
