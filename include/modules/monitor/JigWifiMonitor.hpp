#ifndef JIG_WIFI_MONITOR_HPP
#define JIG_WIFI_MONITOR_HPP

#include <string>
#include <atomic>
#include <chrono>
#include <functional>
#include <thread>

#define MAX_TIME_DIFFERENCE     4

class JigWifiMonitor 
{
public:
    JigWifiMonitor(const std::string&);

    void start_monitoring(std::function<void(bool)> );

    const std::string& get_jig_connection_status(void);

    const std::string& get_jig_network_name(void);

    const std::string& get_jig_mac_address(void);

private:
    std::string jig_connection_status;
    std::string jig_network_name;
    std::string jig_mac_address;
    
    const std::string _disconnected_status = "Disconnected";
    const std::string _disconnected_network = "Network: N/A";
    const std::string _disconnected_mac = "MAC: N/A";

    const std::string jig_wifi_topic;
    
    bool parse_wifi_data(const std::string&);
    void handle_message(const std::string& message);
    void monitoring_loop();

    std::atomic<bool> connected{false};
    std::chrono::steady_clock::time_point last_update_time;

    // Callback to be called from here, implemented in the AppInterface, do whatever you want with it
    std::function<void(bool)> on_status_change_cb;

    std::thread monitor_thread;


};

#endif // JIG_WIFI_MONITOR_HPP