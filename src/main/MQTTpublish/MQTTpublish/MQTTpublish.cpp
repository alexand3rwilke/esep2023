/*
 * QnetClient.cpp
 *
 *  Created on: 19.12.2022
 *  Author: Dresske, Christian
 */

#include "MQTTpublish.h"
#include "../../Imports.h"





#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTT/MQTTClient.h"

//#include "paho/MQTTPacket.h"
//#include "festo_mqtt_send.h"
//#include "transport.h"


// IPv4-Adresse des Brokers (Broker läuft auf RaspberryPi per default (autostart)): "tcp://192.168.101.*:1883"
#define ADDRESS     "tcp://192.168.101.202:1883"
#define CLIENTID    "ExampleClientPub"
// Topic muss im Broker angegeben werden -> darüber Nachrichten empfangen
#define TOPIC       "/Festo/102"
// payload ist hier erstmal Kosmetik, siehe Zeile
#define PAYLOAD     " Start MQTT"
#define QOS         1
//#define TIMEOUT     10L

#define TIMEOUT     10000L


MQTTPublish::MQTTPublish(Dispatcher *disp,ContextData *contextData) {

	this->dispatcher = disp;
	this->contextData =contextData;
	ClientThread = new std::thread([this]() {client();});
}

MQTTPublish::~MQTTPublish() {}

void MQTTPublish::sendToConsole(string wert){
	this->ergebnisString =wert;

}



void MQTTPublish::client(){

	// der Broker sollte bereit sein

	/* ### Create channel - Connecting with Dispatcher ### */
	int channnelID = ChannelCreate(0);//Create channel to receive Events

	if (channnelID < 0) {
		perror("Could not create a channel!\n");
	}

	int pid = getpid();
	int conID = ConnectAttach(0, pid, channnelID, _NTO_SIDE_CHANNEL, 0);

	if (conID < 0) {
		perror("Could not connect to channel!");
	}

	vector<int8_t> events = {MQTTMESSAGE};

	dispatcher->registerForEventWIthConnection(events, conID);

	_pulse msg;

	while (true) {

		cout << "MQTT vor dem Recive" << endl;

		int recvid = MsgReceivePulse(channnelID, &msg, sizeof(_pulse), nullptr);
		cout << "MQTT vor dem Recive ----- danach" << endl;
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
	    //return rc;
	} // while(true)
}
//
//int MQTTPublish:: myMqttPublish(char * payload) {
//	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
//	int rc = 0;
//	int mysock = 0;
//	unsigned char buf[200];
//	int buflen = sizeof(buf);
//	int msgid = 1;
//	MQTTString topicString = MQTTString_initializer;
//	int req_qos = 0;
//	int payloadlen = strlen(payload);
//	int len = 0;
//	char *host = "192.168.101.202";
//	int port = 1883;
//
//	mysock = transport_open(host, port);
//	if(mysock < 0)
//		return mysock;
//
//	printf("Sending to hostname %s port %d\n", host, port);
//
//	data.clientID.cstring = "Sortiermaschine";
//	data.keepAliveInterval = 20;
//	data.cleansession = 1;
//	data.username.cstring = "";
//	data.password.cstring = "";
//
//	len = MQTTSerialize_connect(buf, buflen, &data);
//	rc = transport_sendPacketBuffer(mysock, buf, len);
//
//	/* wait for connack */
//	if (MQTTPacket_read(buf, buflen, transport_getdata) == CONNACK)
//	{
//		unsigned char sessionPresent, connack_rc;
//
//		if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0)
//		{
//			printf("Unable to connect, return code %d\n", connack_rc);
//			transport_close(mysock);
//			return (-1);
//		}
//	}
//	else {
//		transport_close(mysock);
//		return (-1);
//	}
//
//
//
//	/* publish */
//
//	topicString.cstring = "pubtopic";
//
//	len = MQTTSerialize_publish(buf, buflen, 0, 0, 0, 0, topicString, (unsigned char*)payload, payloadlen);
//	rc = transport_sendPacketBuffer(mysock, buf, len);
//
//	printf("disconnecting\n");
//	len = MQTTSerialize_disconnect(buf, buflen);
//	rc = transport_sendPacketBuffer(mysock, buf, len);
//
//	transport_close(mysock);
//
//	return 0;
//}

