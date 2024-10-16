#include <mosquitto.h>
#include <mqtt_protocol.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <jsoncpp/json/json.h>

#define host                "localhost"
#define port                1883
#define SUB_MODBUS_CONTROL  "gw/modbus/control"
#define client_id           "client_sub"

static int run = 1;
static int rc = 0;
int num = 1;
using namespace std;
string message_payload_str;
string message_topic_str;
struct mosquitto *mosq;

char msg_join[] = "hello, connection configured!";

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    cout << "Got message from " << message->topic << " topic" << endl;
    cout << "Content: " << (char*) message->payload << endl;
    message_payload_str = (char*) message->payload;
    message_topic_str = message->topic;

    Json::Reader     reader;
    Json::Value      root;
    Json::FastWriter writer;
    reader.parse(message_payload_str, root);

    cout << root["address"].asInt();
}

int main(int argc, char * argv[]) {
    mosquitto_lib_init();

	mosq = mosquitto_new(client_id, true, NULL);

	if(mosq)
    {
	    mosquitto_connect(mosq, host, port, 60);
        mosquitto_message_callback_set(mosq, message_callback);
        
		mosquitto_subscribe(mosq, NULL, SUB_MODBUS_CONTROL, 0);	}

    while(run)
    {
        mosquitto_loop(mosq, 3000, 1);
    }
} 
