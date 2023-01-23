/*
 * QnetClient.cpp
 *
 *  Created on: 19.12.2022
 *  Author: Dresske, Christian
 */

#include "MQTTpublish.h"
#include "../../Imports.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTT/MQTTClient.h"


// IPv4-Adresse des Brokers (Broker läuft auf RaspberryPi per default (autostart)): "tcp://192.168.101.*:1883"
#define ADDRESS     "tcp://192.168.101.202:1883"
#define CLIENTID    "ExampleClientPub"
// Topic muss im Broker angegeben werden -> darüber Nachrichten empfangen
#define TOPIC       "/Festo/108"
// payload ist hier erstmal Kosmetik, siehe Zeile
#define PAYLOAD     " Start MQTT"
#define QOS         1
#define TIMEOUT     10L

//#define TIMEOUT     10000L


MQTTPublish::MQTTPublish(Dispatcher *disp,ContextData *contextData) {

	this->dispatcher = disp;
	this->contextData =contextData;
}

MQTTPublish::~MQTTPublish() {}

void MQTTPublish::sendToConsole(string wert){
	this->ergebnisString =wert;
	ClientThread = new std::thread([this]() {client();});
}



int MQTTPublish::client(){

	// der Broker sollte bereit sein

	/* ### Create channel - Connecting with Dispatcher ### */
//	int channnelID = ChannelCreate(0);//Create channel to receive Events
//
//	if (channnelID < 0) {
//		perror("Could not create a channel!\n");
//	}
//
//	int pid = getpid();
//	int conID = ConnectAttach(0, pid, channnelID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
//
//	if (conID < 0) {
//		perror("Could not connect to channel!");
//	}
//
//	vector<int8_t> events = {MQTTMESSAGE};
//
//	dispatcher->registerForEventWIthConnection(events, conID);
//
//	_pulse msg;

//	while (true) {
//
//      //Fals irgendwann mal WS an FBM2 ankommen
//		int recvid = MsgReceivePulse(channnelID, &msg, sizeof(_pulse), nullptr);

//		switch(msg.code){
//
//					case MQTTMESSAGE:
//
//					break;
//			}


	    //printf("Running simple MQTT client publish example ");
		fflush(stdout);
	    MQTTClient client;
	    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	    MQTTClient_message pubmsg = MQTTClient_message_initializer;
	    MQTTClient_deliveryToken token;
	    int rc;

	    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
	        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
	    {
	         printf("Failed to create client, return code %d\n", rc);
	         exit(EXIT_FAILURE);
	    }

	    conn_opts.keepAliveInterval = 20;
	    conn_opts.cleansession = 1;
	    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
	    {
	        printf("Failed to connect, return code %d\n", rc);
	        exit(EXIT_FAILURE);
	    }

	    // dieser Stringbuffer wird übertragen !!!!!!!!!!!!!!!!!
	    char payload[40] = "Joshua------------------------!";
	    memset(payload,0,40);
		for (int i = 0; i < ergebnisString.length(); i++) {
			payload[i] = ergebnisString[i];
		    }
	    //char alex[40] = "Alex-------";
	    //strcat(payload,alex);
//	    strcat(payload,contextData->mqtt_msg);
//	    char *payload = new char[sizeof(contextData->getMqtt())];
	    //memset(payload);


	    //string payload = "WS NORMAL MITBOHRUNG 24 23!";
	    pubmsg.payload = payload;
	    pubmsg.payloadlen = (int)strlen(payload);
	    pubmsg.qos = QOS;
	    pubmsg.retained = 0;
	    if ((rc = MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
	    {
	         printf("Failed to publish message, return code %d\n", rc);
	         exit(EXIT_FAILURE);
	    }

//	    printf("Waiting for up to %d seconds for publication of %s\n"
//	            "on topic %s for client with ClientID: %s\n",
//	            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
	    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
	    printf("Message with delivery token %d delivered\n", token);

	    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
	    	printf("Failed to disconnect, return code %d\n", rc);
	    MQTTClient_destroy(&client);
	    return rc;
//	}
}
