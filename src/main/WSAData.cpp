/*
 * WSAData.cpp
 *
 *  Created on: 14.12.2022
 *      Author: Hendrik Marquardt
 */

#include "WSAData.h"

WSAData::WSAData(){
	sorterTyp = 0;
	distance_FB_ADC = 0;
	distance_FWS_ADC = 0;
	distance_WS_ADC = 0;

	distance_LSA_ADC = 0;
	distance_ADC_LSS = 0;
	distance_LSS_LSE = 0;

	fbm1 = false;
	fbm2 = false;
}

WSAData::~WSAData(){

}

//Setter
void WSAData::setSorterTyp(int arg){
	sorterTyp = arg;
}

void WSAData::setDistance_WS_ADC(int arg){
	distance_WS_ADC = arg;
}

void WSAData::setDistance_LSS_LSE(int arg){
	distance_LSS_LSE = arg;
}

void WSAData::setDistance_LSA_ADC(int arg){
	distance_LSA_ADC = arg;
}

void WSAData::setDistance_FWS_ADC(int arg){
distance_FWS_ADC = arg;
}

void WSAData::setDistance_ADC_LSS(int arg){
	distance_ADC_LSS = arg;
}

void WSAData::setDistance_FB_ADC(int arg){
	distance_FB_ADC = arg;
}

void WSAData::setFBM1(bool arg){
	fbm1 = arg;
}

void WSAData::setFBM2(bool arg){
	fbm2 = arg;
}

//Getter
int WSAData::getSorterTyp(){
	return sorterTyp;
}

int WSAData::getDistance_WS_ADC(){
	return distance_WS_ADC;
}

int WSAData::getDistance_LSS_LSE(){
	return distance_LSS_LSE;
}

int WSAData::getDistance_LSA_ADC(){
	return distance_LSA_ADC;
}

int WSAData::getDistance_FWS_ADC(){
	return distance_FWS_ADC;
}

int WSAData::getDistance_ADC_LSS(){
	return distance_ADC_LSS;
}

int WSAData::getDistance_FB_ADC(){
	return distance_FB_ADC;
}

bool WSAData::getFBM(){
	if(fbm1){
		return fbm1;
	}
	return fbm2;
}

