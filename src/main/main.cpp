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
#include <fstream>
#include <iostream>


#include "Imports.h"


int MIN_HOEHE = 3300;
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

			} else {

				FESTO_TYPE = 1;
				system("gns -s");
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


		fstream config;
		string input;
		string delimiter= " ";
		config.open("/esep_gruppe2.2_git/src/main/bspreihenfolgeWK.cfg", ios::in);
		vector<int> werkstuckReihenfolge;

		std::ofstream outfile("/bspreihenfolgeWK.cfg");

		outfile << "my text here!" << std::endl;

		outfile.close();

		if(!config)perror("Fehler beim Öffnen von bspreihenfolgeWK.cfg");
		string werkstueck;


		//TODO EINKOMMENTIEREN
		werkstuckReihenfolge.push_back(WK_Normal);
		werkstuckReihenfolge.push_back(WK_FLACH);
		werkstuckReihenfolge.push_back(WK_Bohrung_Normal);
		// TODO EINKOMMENTIEREN


		//werkstuckReihenfolge.push_back(WK_FLACH);
		//werkstuckReihenfolge.push_back(WK_Bohrung_Normal);
		while(getline(config, input))
		{
			werkstueck = input.substr(input.find(delimiter) + 1, input.length());


			if(werkstueck == "WK_NORMAL")  {
				werkstuckReihenfolge.push_back(WK_Normal);
			}

			else if(werkstueck == "WK_FLACH")  {
				werkstuckReihenfolge.push_back(WK_FLACH);
			}

			else if(werkstueck == "WK_Bohrung_Normal")  {
				werkstuckReihenfolge.push_back(WK_Bohrung_Normal);
			}

			else if(werkstueck == "WK_Bohrung_Metal")  {
				werkstuckReihenfolge.push_back(WK_Bohrung_Metal);
			}


		}

		config.close();

		if(werkstuckReihenfolge.size() == 0) {

			perror("Es wurde keine Reihenfolge bestimmt!");
		}

		for(int wkConfig : werkstuckReihenfolge) {
			cout << wkConfig << " in List eingefügt " << endl;



		}

		ContextData *contextData = new ContextData(&dispatcher,werkstuckReihenfolge);
		Context *context = new Context(&dispatcher, actions,contextData);

		if (strcmp(args[1], "F1") == 0) {

			cout << "Starting Festo FBM1 \n" << endl;
			QnetServer *server = new QnetServer("FBM1",&dispatcher,contextData);
			QnetClient *client = new QnetClient("FBM2",&dispatcher,contextData);
		}
		else if (strcmp(args[1], "F2") == 0) {

			cout << "Starting Festo FBM2 \n" << endl;
			QnetServer *server = new QnetServer("FBM2",&dispatcher,contextData);
			QnetClient *client = new QnetClient("FBM1",&dispatcher,contextData);
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
