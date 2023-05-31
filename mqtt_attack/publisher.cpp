#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "mqtt/async_client.h"

const std::string SERVER_ADDRESS("tcp://localhost:1883");
const std::string CLIENT_ID("mqtt_cpp_async_publisher");
const std::string TOPIC("my/topic");

class callback : public virtual mqtt::callback
{
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "\nConnection lost" << std::endl;
        if (!cause.empty())
            std::cout << "\tcause: " << cause << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {
        std::cout << "\nDelivery complete for token: "
                  << (token ? token->get_message_id() : -1) << std::endl;
    }
};

int main(int argc, char* argv[])
{
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    callback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try {
        std::cout << "Connecting to MQTT server: '" << SERVER_ADDRESS << "'..." << std::flush;
        client.connect(connOpts)->wait();
        std::cout << "OK\n" << std::endl;

        std::string payload = "Hello, MQTT!";
        mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, payload);
	//std::cout << "Topic: " << pubmsg->get_topic() << std::endl;
        pubmsg->set_qos(0);
        client.publish(pubmsg)->wait();
        std::cout << "Published message: " << payload << std::endl;

        std::cout << "Disconnecting from MQTT server..." << std::flush;
        client.disconnect()->wait();
        std::cout << "OK" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
