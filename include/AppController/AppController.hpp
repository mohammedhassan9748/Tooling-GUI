#ifndef APP_INTERFACE_HPP
#define APP_INTERFACE_HPP

#include <string>
#include <atomic>
#include <memory>
#include "Windows.h"
#include "request.hpp"
#include "JigWifiMonitor.hpp"
#include "JigDebugMonitor.hpp"

class AppController
{
private:

    std::shared_ptr<Request> current_request;
    std::unique_ptr<JigWifiMonitor> jig_wifi_monitor = nullptr;    
    std::unique_ptr<JigDebugMonitor> jig_debug_monitor = nullptr;
    RequestHandlerRegistry& reqHandlerRegistry = RequestHandlerRegistry::getInstance();

    HWND a_hwnd;

    // Private constructor to prevent instantiation
    AppController() = default;

    // Delete copy constructor, move constructor, and assignment operators
    AppController(const AppController&) = delete;
    AppController& operator=(const AppController&) = delete;
    AppController(AppController&&) = delete;
    AppController& operator=(AppController&&) = delete;

    void setup_monitor_module(const std::string&);

public:
    // singleton instance
    static AppController& getInstance();

    // --------- change in frontend methods -----------
    void on_connect_button_pressed(void);

    void on_send_button_pressed(void);

    // --------- change in backend methods -----------
    void on_mqtt_connection(void);

    void on_req_response_received(const std::string& response);

    void on_change_wifi_status(bool);

    void on_debug_data_received(const std::string& debugData);

    // destructor
    ~AppController() = default;

};

#endif /* APP_INTERFACE_HPP */