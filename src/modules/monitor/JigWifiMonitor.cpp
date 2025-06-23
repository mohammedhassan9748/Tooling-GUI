#include "JigWifiMonitor.hpp"
#include "mqtt_manager.hpp"
#include "CmdConfig.hpp"

JigWifiMonitor::JigWifiMonitor(const std::string& jigID):
    jig_wifi_topic(jigID + "/" + JIG_WIFI_TOPIC)
{
    jig_connection_status = _disconnected_status;
    jig_network_name = _disconnected_network;
    jig_mac_address = _disconnected_mac;

    MqttManager::getInstance().register_on_message_callback(
        jig_wifi_topic,
        [this](const std::string& message) {
            handle_message(message);
        }
    );
}

bool JigWifiMonitor::parse_wifi_data(const std::string& sent_data)
{
    // Parse the message to extract connection status, network name, and MAC address, separated by #.
    size_t pos1 = sent_data.find('#');
    size_t pos2 = sent_data.find('#', pos1 + 1);
    if (pos1 == std::string::npos || pos2 == std::string::npos) 
    {
        return false; // Invalid message format
    }
    this->jig_connection_status = sent_data.substr(0, pos1);
    this->jig_network_name = sent_data.substr(pos1 + 1, pos2 - pos1 - 1);
    this->jig_mac_address = sent_data.substr(pos2 + 1);
    return true;
}

void JigWifiMonitor::handle_message(const std::string& message)
{
    /* Handling a message means, either it is first time to enter after application started or reconnection(the esp disconnected and reconnected
    back again), or already connected and just ensuring connection */
    // Check if already connection was established:
    if(this->connected.load())
    {
        // It is already connected, no need to re parse the data
    }
    else
    {
        if (parse_wifi_data(message)) {
            this->connected.store(true);
        }
        if (on_status_change_cb) {
            on_status_change_cb(true);
        }
    }
    last_update_time = std::chrono::steady_clock::now();
}

void JigWifiMonitor::start_monitoring(std::function<void(bool)> callback)
{
    on_status_change_cb = std::move(callback);
    monitor_thread = std::thread(&JigWifiMonitor::monitoring_loop, this);
    monitor_thread.detach();
}

void JigWifiMonitor::monitoring_loop()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - this->last_update_time);
        if(diff.count() > MAX_TIME_DIFFERENCE && connected.load())
        {
            // Change happened, it was connected and now it is disconnected
            connected.store(false);
            this->jig_connection_status = this->_disconnected_status;
            this->jig_network_name = this->_disconnected_network;
            this->jig_mac_address = this->_disconnected_mac;
            if (on_status_change_cb) {
                on_status_change_cb(false);
            }
        }
    }
}

const std::string& JigWifiMonitor::get_jig_connection_status(void)
{
    return this->jig_connection_status;
}

const std::string& JigWifiMonitor::get_jig_network_name(void)
{
    return this->jig_network_name;
}

const std::string& JigWifiMonitor::get_jig_mac_address(void)
{
    return this->jig_mac_address;
}
