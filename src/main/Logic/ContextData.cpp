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

void ContextData::setZielWk(int wkType) {
    zielWk = wkType;
}

int ContextData::getZielWk() {
  return zielWk;
}


void ContextData::setErkanntesWk(int wkType) {
    erkanntesWk = wkType;
}

int ContextData::getErkanntesWk() {
  return erkanntesWk;
}
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
