/*
 * File:   contextdata.cpp
 * @author Lehmann
 * @date April 12, 2019
 */

#include "contextdata.h"
#include <iostream>

using namespace std;

ContextData::ContextData(Dispatcher *dispatcher) {
disp = dispatcher;
gescanntesWKMap = {};
gesuchtesWKMap = {};


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

}

void ContextData::removeWK() {
	if(wkCounter> 1) {
		wkCounter--;
	}

}

int ContextData::getWKCount() {
	return wkCounter;

}

void ContextData::setGesuchtWKMapForStateForIndex(int index, int gesuchtesWK) {
	gesuchtesWKMap[index] = gesuchtesWK;
	cout << "Gesuchtes WK wurde auf folgendes gesetzt:" << gesuchtesWKMap[index] << endl; // just for illustration.



}


void ContextData::setGescanntWKMapForStateForIndex(int index,int gescanntesWK) {
	 gescanntesWKMap[index] = gescanntesWK;

}


int ContextData::getGesuchtWKMapForStateForIndex(int index) {
	return gesuchtesWKMap[index];


}


int ContextData::getGescanntWKMapForStateForIndex(int index) {
	return  gescanntesWKMap[index];

}
