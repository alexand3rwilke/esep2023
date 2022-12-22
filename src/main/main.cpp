/*
 * main.cpp
 *
 *  Created on: 25.10.2022
 *      Author: Alexander Wilke
 */

#ifndef RUN_TESTS

#include "hal/Actuator.h"
#include "hal/Sensor.h"
#include "hal/ADC_Service.h"
#include "ADC/ADC.h"
#include "ADC/TSCADC.h"

#include "ISR/ISR.h"
#include "dispatcher/Dispatcher.h"
#include "Logic/Context.h"
#include "Logic/Actions.h"
#include "Qnet/QnetClient/QnetClient.h"
#include "Qnet/QnetServer/QnetServer.h"

#include "Imports.h"


int MIN_HOEHE = 3580;
int MAX_HOEHE = 2100;

using namespace std;

void wait(int seconds) {
	usleep(1000 * (seconds * 1000 ));
}


int FESTO_TYPE;
int main(int argc, char** args) {

			if (strcmp(args[1], "F1") == 0) {
				FESTO_TYPE = 1;
				system("gns -s");

			}
			else if (strcmp(args[1], "F2") == 0) {
				FESTO_TYPE = 2;
				system("gns");

			}

	 cout << "Im Festo:" << FESTO_TYPE << endl;

	cout << "Starting Festo Test \n" << endl;

		Dispatcher dispatcher;

		WSAData *wsa_data = new WSAData();
		ISR *isr = new ISR(&dispatcher);
		Sensor *sensor = new Sensor(&dispatcher);
		TSCADC tscadc;
		ADC* adc = new ADC(tscadc);
		Actions *actions = new Actions(&dispatcher);
		Actuator *actuator = new Actuator(&dispatcher);
		ADC_Service *adcService = new ADC_Service(&dispatcher);

		ContextData *contextData = new ContextData(&dispatcher);
		// TODO Entfernen, nut zum testen der aussortierung.
		// Nachher zu ersetzen mit Werten aus ausgelesender Liste
		contextData->setZielWk(WK_Normal);

		Context *context = new Context(&dispatcher, actions,contextData);

		if (strcmp(args[1], "F1") == 0) {

			cout << "Starting Festo FBM1 \n" << endl;
			QnetServer *server = new QnetServer("FBM1",&dispatcher);
			QnetClient *client = new QnetClient("FBM2",&dispatcher);
		}
		else if (strcmp(args[1], "F2") == 0) {

			cout << "Starting Festo FBM2 \n" << endl;
			QnetServer *server = new QnetServer("FBM2",&dispatcher);
			QnetClient *client = new QnetClient("FBM1",&dispatcher);
		}
//
//			cout << "Starting Festo FBM1 \n" << endl;
//			QnetServer *server = new QnetServer("FBM1",&dispatcher);
//			QnetClient *client = new QnetClient("FBM2",&dispatcher);
//		}
//		else if (strcmp(args[1], "-FBM2") == 0) {
//
//			cout << "Starting Festo FBM2 \n" << endl;
//			QnetServer *server = new QnetServer("FBM2",&dispatcher);
//			QnetClient *client = new QnetClient("FBM1",&dispatcher);
//		}
	//TODO: Besseres warten
	 while(true){
	 }

	return EXIT_SUCCESS;
}







void playDemo() {


//				Dispatcher dispatcher;
//
//
//				// Muss keine Events verschicken, nur annehmen
//				Actuator *actuator = new Actuator(&dispatcher);
//
//				// Move Assambly Left
//			 	actuator->assamblyMoveLeftOn();
//			 	wait(3);
//			 	actuator->assamblyMoveLeftOff();
//
//			 	// Move Assambly Right
//			 	actuator->assamblyMoveRightOn();
//			 	wait(3);
//			 	actuator->assamblyMoveRightOff();
//
//			 	// Move Assambly Slow
//			 	actuator->assamblyMoveRightOn();
//			 	actuator->assamblyMoveSlowOn();
//			 	wait(3);
//			 	actuator->assamblyMoveSlowOff();
//			 	actuator->assamblyMoveRightOff();
//
//			 	// Open Switch
//			 	actuator->switchOn();
//			 	wait(3);
//			 	actuator->switchOff();
//
//			 	// LED On
//			 	actuator->redOn();
//			 	actuator->yellowOn();
//			 	actuator->greenOn();
//			 	wait(3);
//			 	actuator->redOff();
//			 	actuator->yellowOff();
//			 	actuator->greenOff();

}




#endif
