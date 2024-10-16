#include <mosquitto.h>
#include <mqtt_protocol.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <jsoncpp/json/json.h>

#define host                "Mqtt.mysignage.vn"
// #define host                "localhost"
#define port                1883
#define PUB_MODBUS_CONTROL  "gw/modbus/control"
#define client_id           "client_pub"

int on = 1;
int off = 1;
int get_type = 1;
using namespace std;
const char* msg_on;
const char* msg_off;
struct mosquitto *mosq;

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    cout << "Got message from " << message->topic << " topic" << endl;
    cout << "Content: " << (char*) message->payload << endl;
}

void CreateMessage()
{
    Json::Value message_on;
    Json::Value message_off;

    message_on["address"] = 0x30;
    message_on["field"] = "value";
    message_on["value"] =  255;
    message_on["position"] = 103;

    message_off["address"] = 0x30;
    message_off["field"] = "value";
    message_off["value"] =  0;
    message_off["position"] = 103;

	string json_string_parse_on;
    string json_string_parse_off;
	Json::FastWriter writer;
	json_string_parse_on = writer.write(message_on);
    json_string_parse_off = writer.write(message_off);

    msg_on = json_string_parse_on.c_str();
    msg_off = json_string_parse_off.c_str();

    cout << msg_on << endl << msg_off << endl;
}

int main(int argc, char * argv[])
{
    mosquitto_lib_init();

	mosq = mosquitto_new(client_id, true, NULL);

    if(mosq)
    {
	    mosquitto_connect(mosq, host, port, 60);
        mosquitto_message_callback_set(mosq, message_callback);
	}
    
    Json::Value message_on;
    Json::Value message_off;

    message_on["address"] = 0x30;
    message_on["field"] = "value";
    message_on["value"] =  255;
    message_on["position"] = 103;

    message_off["address"] = 0x30;
    message_off["field"] = "value";
    message_off["value"] =  0;
    message_off["position"] = 103;

	string json_string_parse_on;
    string json_string_parse_off;
	Json::FastWriter writer;
	json_string_parse_on = writer.write(message_on);
    json_string_parse_off = writer.write(message_off);

    msg_on = json_string_parse_on.c_str();
    msg_off = json_string_parse_off.c_str();

    cout << msg_on << endl << msg_off << endl;

    while(1)
    {
        cout << "Connection remains active" << endl;
        cout << "Sending message message on: " << on++ << endl << endl;
        cout << msg_on << endl;
        mosquitto_publish(mosq, NULL, PUB_MODBUS_CONTROL, strlen(msg_on), msg_on, 0, false);
        usleep(500000);

        cout << "Sending message message off: " << off++ << endl << endl;
        cout << msg_off << endl;
        mosquitto_publish(mosq, NULL, PUB_MODBUS_CONTROL, strlen(msg_off), msg_off, 0, false);
        usleep(500000);
        mosquitto_loop(mosq, -1, 1);
    }
} 
