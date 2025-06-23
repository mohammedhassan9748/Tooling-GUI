#ifndef MQTT_MANAGER_HPP
#define MQTT_MANAGER_HPP

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "mosquitto.h"

enum class MqttErrorCode {
    SUCCESS,
    ERROR_EMPTY_BROKER_IP,
    ERROR_EMPTY_PORT_NUM,
    ERROR_INVALID_PORT_NUM,
    ERROR_COULD_NOT_CREATE_CLIENT,
    ERROR_COULD_NOT_CONNECT,
    ERROR_COULD_NOT_START_LOOP,
    ERROR_COULD_NOT_SUBSCRIBE_WHILE_REGISTERING_CALLBACK,
};

class MqttManager
{
private:

    std::map<MqttErrorCode, std::string> error_messages = {
        {MqttErrorCode::SUCCESS, "Success"},
        {MqttErrorCode::ERROR_EMPTY_BROKER_IP, "Broker IP cannot be empty."},
        {MqttErrorCode::ERROR_EMPTY_PORT_NUM, "Port number cannot be empty."},
        {MqttErrorCode::ERROR_INVALID_PORT_NUM, "Port number entered is not numeric value"},
        {MqttErrorCode::ERROR_COULD_NOT_CREATE_CLIENT, "Could not create Mosquitto client."},
        {MqttErrorCode::ERROR_COULD_NOT_CONNECT, "Could not connect to the MQTT broker."},
        {MqttErrorCode::ERROR_COULD_NOT_START_LOOP, "Could not start the MQTT loop."},
        {MqttErrorCode::ERROR_COULD_NOT_SUBSCRIBE_WHILE_REGISTERING_CALLBACK, "Could not subscribe to topic while registering callback."},
        // Add more error codes and messages as needed
    };

    std::string broker_ip;
    std::string port_num;

    struct mosquitto* mosq = nullptr;
    
    bool is_connected = false;

    std::map<std::string, std::function<void(const std::string)>> subscribed_topics_callbacks;
    std::vector<std::function<void(void)>> on_connect_callback_fns;
    std::vector<std::function<void(void)>> on_disconnect_callback_fns;

    // RAII - Rule(0)
    MqttManager() = default; // Delete default constructor
    // copy constructor
    MqttManager(const MqttManager&) = delete;
    // move constructor
    MqttManager(MqttManager&&) = delete;
    // copy assignment operator
    MqttManager& operator=(const MqttManager&) = delete;
    // move assignment operator
    MqttManager& operator=(MqttManager&&) = delete;

    static void on_connect(struct mosquitto*, void*, int rc);
    static void on_disconnect(struct mosquitto*, void *userdata, int rc);
    static void on_message(struct mosquitto*, void *userdata, const struct mosquitto_message *message);

public:
    // singleton class
    static MqttManager& getInstance(void);

    // init the mosquitto mqtt
    MqttErrorCode set_broker_ip(const std::string&);
    MqttErrorCode set_port_num(const std::string&);
    
    // Function to initialize the mosquitto library
    MqttErrorCode init(void);
    void publish(const std::string, const std::string&, int qos, bool retain);

    bool register_on_connect_callback(std::function<void(void)> callback);
    bool register_on_disconnect_callback(std::function<void(void)> callback);
    bool register_on_message_callback(const std::string& topic, std::function<void(const std::string&)> callback);
    bool unregister_on_message_callback(const std::string& topic);

    // check if connected client to broker
    bool isConnected(void) const;
    // get error message
    std::string get_error_message(MqttErrorCode code) const;



    // destructor
    ~MqttManager() = default;

};

#endif /* MQTT_MANAGER_HPP */
