/*
 * File:   contextdata.h
 * @author Lehmann
 * @date April 12, 2019
 */

#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H

#include "../dispatcher/Dispatcher.h"

class ContextData{
private:
    int errorCounter = 0;
    bool rampe1Voll = false;
    bool rampe2Voll = false;
    int zielWk = 0;
    int erkanntesWk = 0;
    int wkCounter = 0;

public:
    Dispatcher *disp;
    ContextData(Dispatcher *dispatcher);
    ~ContextData();
    void incErrorCounter();
    void clearErrorcounter();
    void show();

    //Rampen logik
    void setRampe1Voll(bool value);
    void setRampe2Voll(bool value);
    bool getRampe1Voll();
    bool getRampe2Voll();

    //Das Werkstück welches erwartet wird
    void setZielWk(int wkType);
    int getZielWk();


    //Das Werkstück welches erwartet wird
    void setErkanntesWk(int wkType);
    int getErkanntesWk();

    //WK Counter Methoden
    void addWK();
    void removeWK();

    int conIDDis = 0;
};


#endif /* CONTEXTDATA_H */
