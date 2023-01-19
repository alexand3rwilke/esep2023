/*
 * File:   contextdata.h
 * @author Lehmann
 * @date April 12, 2019
 */

#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H
using namespace std;

#include "../dispatcher/Dispatcher.h"


class ContextData{
private:
    int errorCounter = 0;
    bool rampe1Voll = false;
    bool rampe2Voll = false;
    int zielWk = 0;
    int erkanntesWk = 0;
    int wkCounter = 0;
    bool wkAufFBM2;
    string mqtt = "Test MQTT mit sting";
    map<int, int> gesuchtesWKMap;
    map<int, int> gescanntesWKMap;
    std::vector<int> adcWaitList;

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
    //void setZielWk(int wkType);
    //int getZielWk();


    //Das Werkstück welches erwartet wird
    //void setErkanntesWk(int wkType);
    //int getErkanntesWk();

    //WK Counter Methoden
    void addWK();
    void removeWK();
    int getWKCount();

    // WK gesucht & gescannt map
    void setGesuchtWKMapForStateForIndex(int index, int gesuchtesWK);
    void setGescanntWKMapForStateForIndex(int index,int gescanntesWK);
    int getGesuchtWKMapForStateForIndex(int index);
    int getGescanntWKMapForStateForIndex(int index);
    bool isPresentInMap(int index);

    void registerForAdc(int stateId);

    int getLatestRegisterForAdcState();
    void setWkOnFMB2(bool wkAufFBM2);
    bool getWkOnFMB2();
    char mqtt_msg[40];

	const char* getMqttMsg() {
		char *mqtt_msg = new char[mqtt.length()+1];
	    strcpy(mqtt_msg, mqtt.c_str());
		return mqtt_msg;
	}

	string getMqtt() {

		return mqtt;
	}

	void setMqtt( string mqtt) {
		this->mqtt = mqtt;
	}

    int conIDDis = 0;
};


#endif /* CONTEXTDATA_H */
