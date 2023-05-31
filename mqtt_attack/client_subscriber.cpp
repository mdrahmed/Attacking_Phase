#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "mqtt/async_client.h"

const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("mqtt_cpp_async_subscriber");
const std::string TOPIC("my/topic");

class mqtt_callback : public virtual mqtt::callback
{
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "\nConnection lost" << std::endl;
        if (!cause.empty())
            std::cout << "cause: " << cause << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {
        std::cout << "\nDelivery complete for token: "
                  << (token ? token->get_message_id() : -1) << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {
	//std::cout << "msg topic addr: " << &msg->get_topic() << std::endl;
	//printf("Topic from src: %s\n", msg->get_topic().c_str());	
	//printf("Message Content Length: %lu\n", msg->get_payload().length());        
	//std::cout << "Message received on topic: " << msg->get_topic() << std::endl;
        std::cout << "Message content: " << msg->to_string() << std::endl;
    }
};

int main(int argc, char* argv[])
{
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    mqtt_callback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try {
        std::cout << "Connecting to MQTT server: '" << SERVER_ADDRESS << "'..." << std::flush;
        mqtt::token_ptr conntok = client.connect(connOpts);
        conntok->wait();
        std::cout << "OK\n" << std::endl;

        std::cout << "Subscribing to topic: " << TOPIC << "..." << std::flush;
        mqtt::token_ptr subtok = client.subscribe(TOPIC, 0);
        subtok->wait();
        std::cout << "OK\n" << std::endl;

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "Disconnecting from MQTT server..." << std::flush;
        mqtt::token_ptr disconntok = client.disconnect();
        disconntok->wait();
        std::cout << "OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
