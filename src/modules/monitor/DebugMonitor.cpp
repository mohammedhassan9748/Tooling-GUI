#include "JigDebugMonitor.hpp"
#include "mqtt_manager.hpp"
#include "CmdConfig.hpp"

JigDebugMonitor::JigDebugMonitor(const std::string& jigID): 
jig_debug_topic(jigID + "/" + JIG_DEBUG_TOPIC)
{
    // Subscribe to the MQTT topic for the given jigID
    MqttManager::getInstance().register_on_message_callback(jig_debug_topic,
    [this](const std::string& message)
    {
        current_debug_data = message;
        if (on_debug_data_cb)
        {
            on_debug_data_cb(current_debug_data);
        }
    });
}

void JigDebugMonitor::set_on_debug_data_callback(std::function<void(const std::string&)> callback)
{
    on_debug_data_cb = std::move(callback);
}