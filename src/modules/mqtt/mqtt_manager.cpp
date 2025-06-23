#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "mqtt_manager.hpp"

// Private static methods for callbacks
void MqttManager::on_connect(struct mosquitto *mosq, void *userdata, int rc)
{
    if (rc == MOSQ_ERR_SUCCESS) {
        // Connection successful
        std::cout << "Connected to MQTT broker successfully." << std::endl;
        if (userdata) {
            static_cast<MqttManager*>(userdata)->is_connected = true;
            // Finally, subscribe to the topics that have callbacks registered
            for (const auto& topic_callback : static_cast<MqttManager*>(userdata)->subscribed_topics_callbacks) {
                std::cout << "Subscribing to topic: " << topic_callback.first << std::endl;
                int subscribe_rc = mosquitto_subscribe(static_cast<MqttManager*>(userdata)->mosq, NULL, topic_callback.first.c_str(), 1); // QoS 1 for example
            }
            for (const auto& callback : static_cast<MqttManager*>(userdata)->on_connect_callback_fns) {
                std::cout << "Executing on_connect callback." << std::endl;
                callback();
            }
        }
    }
}

void MqttManager::on_disconnect(struct mosquitto *mosq, void *userdata, int rc)
{
    // Handle disconnection
    if (userdata) {
        static_cast<MqttManager*>(userdata)->is_connected = false;
        mosquitto_destroy(static_cast<MqttManager*>(userdata)->mosq);
        static_cast<MqttManager*>(userdata)->mosq = nullptr; // Set to nullptr to avoid dangling pointer
        mosquitto_lib_cleanup();
        for (const auto& callback : static_cast<MqttManager*>(userdata)->on_disconnect_callback_fns) {
            callback();
        }
    }
}

void MqttManager::on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    // Handle incoming messages
    const std::string payloadStr =  std::string(static_cast<char*>(message->payload), message->payloadlen);
    auto it = getInstance().subscribed_topics_callbacks.find(message->topic);
    if (it != getInstance().subscribed_topics_callbacks.end())
    {
        it->second(payloadStr);
    }
}

// Singleton instance

MqttManager& MqttManager::getInstance()
{
    static MqttManager instance;
    return instance;
}


// Public methods 

MqttErrorCode MqttManager::set_broker_ip(const std::string& ip)
{
    if(ip.empty()) 
    {
        return MqttErrorCode::ERROR_EMPTY_BROKER_IP;   
    }
    this->broker_ip = ip;
    return MqttErrorCode::SUCCESS;
}

MqttErrorCode MqttManager::set_port_num(const std::string& port)
{
    if(port.empty())
    {
        return MqttErrorCode::ERROR_EMPTY_PORT_NUM;
    }

    if(!std::all_of(port.begin(),port.end(),::isdigit))
    {
        return MqttErrorCode::ERROR_INVALID_PORT_NUM;
    }

    this->port_num = port;
    return MqttErrorCode::SUCCESS;
}

MqttErrorCode MqttManager::init(void)
{
    mosquitto_lib_init();
   
    this->mosq = mosquitto_new(nullptr, true, this);
    if (!this->mosq) 
    {
        mosquitto_lib_cleanup();
        return MqttErrorCode::ERROR_COULD_NOT_CREATE_CLIENT;
    }
    
    // Set up callbacks for connection and message handling if needed
    mosquitto_connect_callback_set(this->mosq, &MqttManager::on_connect);
    mosquitto_message_callback_set(this->mosq, &MqttManager::on_message);
    mosquitto_disconnect_callback_set(this->mosq, &MqttManager::on_disconnect);

    int rc = mosquitto_connect(this->mosq, this->broker_ip.c_str(), std::stoi(this->port_num), 60);
    if (rc != MOSQ_ERR_SUCCESS) 
    {
        mosquitto_destroy(this->mosq);
        this->mosq = nullptr; // Set to nullptr to avoid dangling pointer
        mosquitto_lib_cleanup();
        return MqttErrorCode::ERROR_COULD_NOT_CONNECT;
    }
    
    // Start the network loop
    rc = mosquitto_loop_start(this->mosq);
    if (rc != MOSQ_ERR_SUCCESS)
    {
        mosquitto_destroy(this->mosq);
        this->mosq = nullptr; // Set to nullptr to avoid dangling pointer
        mosquitto_lib_cleanup();
        return MqttErrorCode::ERROR_COULD_NOT_START_LOOP;
    }

    return MqttErrorCode::SUCCESS;
}

void MqttManager::publish(const std::string topic, const std::string &payload, int qos=0, bool retain=false)
{
    if (!this->mosq) {
        throw std::runtime_error("Mosquitto instance is not initialized.");
    }

    int rc = mosquitto_publish(this->mosq, NULL, topic.c_str(), payload.size(), payload.c_str(), qos, retain);
    if (rc != MOSQ_ERR_SUCCESS) {
        throw std::runtime_error("Failed to publish message: " + std::string(mosquitto_strerror(rc)));
    }
}

bool MqttManager::isConnected(void) const
{
    return this->is_connected;
}

bool MqttManager::register_on_connect_callback(std::function<void(void)> callback)
{
    if (callback) {
        this->on_connect_callback_fns.push_back(callback);
        return true;
    }
    return false;
}

bool MqttManager::register_on_disconnect_callback(std::function<void(void)> callback)
{
    if (callback) {
        this->on_disconnect_callback_fns.push_back(callback);
        return true;
    }
    return false;
}

bool MqttManager::register_on_message_callback(const std::string& topic, std::function<void(const std::string&)> callback)
{
    if (topic.empty() || callback == nullptr) {
        return false; // Topic cannot be empty and callback cannot be null
    }

    this->subscribed_topics_callbacks[topic] = callback;

    if(!this->mosq || !this->is_connected)
    {
        // If not initialized, we cannot register the callback right now
    }
    else
    {
        // Subscribe to the topic with the given QoS
        int rc = mosquitto_subscribe(this->mosq, NULL, topic.c_str(), 1); // QoS 1 for example
        if (rc != MOSQ_ERR_SUCCESS) {
            this->subscribed_topics_callbacks.erase(topic);
            return false; // Subscription failed
        }
    }
    return true;
}

bool MqttManager::unregister_on_message_callback(const std::string& topic)
{
    auto it = this->subscribed_topics_callbacks.find(topic);
    if (it != this->subscribed_topics_callbacks.end()) {
        this->subscribed_topics_callbacks.erase(it);
        if (this->mosq) {
            int rc = mosquitto_unsubscribe(this->mosq, NULL, topic.c_str());
            if (rc != MOSQ_ERR_SUCCESS) return false; // Unsubscription failed
        }
        return true;
    }
    return false;
}

std::string MqttManager::get_error_message(MqttErrorCode code) const
{
    auto it = this->error_messages.find(code);
    if (it != this->error_messages.end()) {
        return it->second;
    }
    return "Unknown error code.";
}