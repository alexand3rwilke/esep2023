/*
 * File:   contextdata.cpp
 * @author Lehmann
 * @date April 12, 2019
 */

#include "contextdata.h"
#include <iostream>

using namespace std;

ContextData::ContextData(Dispatcher *dispatcher, vector<int> werkstuckReihenfolge) {
disp = dispatcher;
gescanntesWKMap = {};
gesuchtesWKMap = {};
wkAufFBM2 = false;
wkReihenfolgeIndex = 0;
this->werkstuckReihenfolgeList = werkstuckReihenfolge;

//adcWaitList = {};



}


ContextData::~ContextData() {
	//delete coID;
}


void ContextData::clearErrorcounter() {
    errorCounter = 0;
}

void ContextData::incErrorCounter() {
    errorCounter++;
    show();
}

void ContextData::show() {
    cout << "error counter:" << errorCounter << endl; // just for illustration.
}

void ContextData::setRampe1Voll(bool value) {
   rampe1Voll = value;
}

void ContextData::setRampe2Voll(bool value) {
   rampe2Voll = value;
}
bool ContextData::getRampe1Voll() {
   return rampe1Voll;
}

bool ContextData::getRampe2Voll() {
   return rampe2Voll;
}

//void ContextData::setZielWk(int wkType) {
//    zielWk = wkType;
//}

//int ContextData::getZielWk() {
//  return zielWk;
//}


//void ContextData::setErkanntesWk(int wkType) {
//    erkanntesWk = wkType;
//}

//int ContextData::getErkanntesWk() {
//  return erkanntesWk;
//}
void ContextData::addWK() {

	wkCounter++;
	printf("Now WK count is : %d  \n",wkCounter);

}

void ContextData::removeWK() {
	if(wkCounter>= 1) {
		wkCounter--;
		printf("Now WK count is : %d \n",wkCounter);
	}

}

int ContextData::getWKCount() {
	return wkCounter;

}

void ContextData::setGesuchtWKMapForStateForIndex(int index, int gesuchtesWK) {

	gesuchtesWKMap[index] = gesuchtesWK;
	cout << "Gesuchtes WK wurde auf folgendes gesetzt:" << gesuchtesWKMap[index] << endl; // just for illustration.



}


void ContextData::setGescanntWKMapForStateForIndex(int index,int gescanntesWK, int durchschnittHoehe) {

	Werkstueck wk;
	wk.setAbsoluteHoehe(0);
	wk.setAussortieren(false);
	wk.setMittlereHoehe(durchschnittHoehe);
	wk.setWkFlipped(false);
	wk.setWkType(gescanntesWK);
	gescanntesWKMap[index] = wk;

}

void ContextData::setGescanntWKMapForStateForIndex(int index,int gescanntesWK, int durchschnittHoehe,bool flipped,bool aussortieren,int absuluteHoehe) {

	Werkstueck wk;
	wk.setAbsoluteHoehe(0);
	wk.setAussortieren(aussortieren);
	wk.setMittlereHoehe(durchschnittHoehe);
	wk.setWkFlipped(flipped);
	wk.setWkType(gescanntesWK);
	gescanntesWKMap[index] = wk;

}


void ContextData::setGescanntWKType(int stateID, int wkType) {
	Werkstueck wk;
	wk = gescanntesWKMap.at(stateID);
	wk.setWkType(wkType);
	gescanntesWKMap[stateID] = wk;

}

void ContextData::setAussortierenForWerkstueckInStateID(int stateID, bool value) {
Werkstueck wk;
wk = gescanntesWKMap.at(stateID);
wk.aussortieren = value;
gescanntesWKMap[stateID] = wk;
}

void ContextData::setFlippedForWerkstueckInStateID(int stateID, bool value) {
Werkstueck wk;
wk = gescanntesWKMap.at(stateID);
wk.wkFlipped = value;
gescanntesWKMap[stateID] = wk;
}



bool ContextData::getAussortierenForWerkstueckInStateID(int stateID) {
Werkstueck wk;
wk = gescanntesWKMap.at(stateID);
return wk.aussortieren;

}

bool ContextData::getFlippedForWerkstueckInStateID(int stateID) {
Werkstueck wk;
wk = gescanntesWKMap.at(stateID);
return wk.wkFlipped;

}



int ContextData::getGesuchtWKMapForStateForIndex(int index) {

	return gesuchtesWKMap.at(index);


}


Werkstueck ContextData::getGescanntWKMapForStateForIndex(int index) {

	return  gescanntesWKMap.at(index);

}

bool ContextData::isPresentInMap(int index) {
	return  gescanntesWKMap.count(index) > 0;

}

void ContextData::registerForAdc(int stateId){
	adcWaitList.push_back(stateId);

	for(int bla : adcWaitList) {
		cout << "State wartet auf ADC :" << bla << endl; // just for illustration.

	}


}

int ContextData::getLatestRegisterForAdcState() {

	if(!adcWaitList.empty()) {

		int stateAdcId = adcWaitList.at(adcWaitList.size()-1);
			adcWaitList.pop_back();
			return stateAdcId;

	}

		return -1;
}

void ContextData::setWkOnFMB2(bool wkAufFBM2) {

this->wkAufFBM2 = wkAufFBM2;
}


bool ContextData::getWkOnFMB2() {


	return wkAufFBM2;
  }

   void ContextData::increaseWkReihenfolgeIndex() {

	   wkReihenfolgeIndex++;
   }





