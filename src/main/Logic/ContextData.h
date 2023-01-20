/*
 * File:   contextdata.h
 * @author Lehmann
 * @date April 12, 2019
 */

#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
using namespace std;

#include "../dispatcher/Dispatcher.h"
#include "Werkstueck.h"
//#include "../MQTTpublish/MQTTpublish/MQTTpublish.h"


class ContextData{
private:
    int errorCounter = 0;
    bool rampe1Voll = false;
    bool rampe2Voll = false;
    int zielWk = 0;
    int erkanntesWk = 0;
    int wkCounter = 0;
    bool wkAufFBM2 = false;

    int wkReihenfolgeIndex;
    bool f2Running = false;

    map<int, int> gesuchtesWKMap;
    map<int, Werkstueck> gescanntesWKMap;
    std::vector<int> adcWaitList;

    bool Lse1Free = true;

public:
    void setLs1Free(bool b);
    bool isLse1Free();
    Dispatcher *disp;
    vector<int> werkstuckReihenfolgeList;
    ContextData(Dispatcher *dispatcher, vector<int> werkstuckReihenfolge);
    ~ContextData();
    void incErrorCounter();
    void clearErrorcounter();
    void show();

    //Rampen logik
    void setRampe1Voll(bool value);
    void setRampe2Voll(bool value);
    bool getRampe1Voll();
    bool getRampe2Voll();

    //WK Counter Methoden
    void addWK();
    void removeWK();
    int getWKCount();
    void resetCount();

    // WK gesucht & gescannt map
    void setGesuchtWKMapForStateForIndex(int index, int gesuchtesWK);
    void setGescanntWKMapForStateForIndex(int index,int gescanntesWK, int durchschnittHoehe);
    void setGescanntWKMapForStateForIndex(int index,int gescanntesWK, int durchschnittHoehe,bool flipped,bool aussortieren,int absuluteHoehe);
    int getGesuchtWKMapForStateForIndex(int index);
    Werkstueck getGescanntWKMapForStateForIndex(int index);
    bool isPresentInMap(int index);

    void registerForAdc(int stateId);

    int getLatestRegisterForAdcState();
    void setWkOnFMB2(bool wkAufFBM2);
    bool getWkOnFMB2();

    void resetContextData();


    int conIDDis = 0;

    void increaseWkReihenfolgeIndex();
	int getwkReihenfolgeIndex() {
		return wkReihenfolgeIndex;
	}
	bool getF2Running()  {
		return f2Running;
	}

	void setF2Running(bool f2Running = false) {
		this->f2Running = f2Running;
	}

	void setAussortierenForWerkstueckInStateID(int stateID, bool value);
	void setFlippedForWerkstueckInStateID(int stateID, bool value);
	bool getAussortierenForWerkstueckInStateID(int stateID);
	bool getFlippedForWerkstueckInStateID(int stateID);


    //Das Werkstück welches erwartet wird
    //void setZielWk(int wkType);
    //int getZielWk();


    //Das Werkstück welches erwartet wird
    //void setErkanntesWk(int wkType);
    //int getErkanntesWk();

};


#endif /* CONTEXTDATA_H */
