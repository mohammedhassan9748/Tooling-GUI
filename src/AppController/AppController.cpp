#include <sstream>
#include <memory>
#include <future>
#include "AppController.hpp"

#include "00_main_window.hpp"

#include "03_jig_id.hpp"
#include "04_server.hpp"
#include "05_connect_button.hpp"
#include "06_connection_status.hpp"

#include "03_request_gui.hpp"
#include "05_req_output_terminal.hpp"
#include "06_jig_wifi.hpp"
#include "07_debug_output_terminal.hpp"

#include "mqtt_manager.hpp"
#include "Request.hpp"
#include "IRequestHandler.hpp"
#include "RequestHandlerRegistry.hpp"
#include "SetErrorReqHandler.hpp"
#include "SetTestReqHandler.hpp"
#include "SetChannelReqHandler.hpp"
#include "ClearErrorReqHandler.hpp"
#include "ClearTestReqHandler.hpp"
#include "ClearChannelReqHandler.hpp"
#include "GetErrorReqHandler.hpp"
#include "GetTestReqHandler.hpp"
#include "GetChannelReqHandler.hpp"

AppController& AppController::getInstance()
{
    static AppController instance; // Guaranteed to be destroyed, instantiated on first use
    return instance;
}

void AppController::on_connect_button_pressed(void)
{
    /**
     * The App Controller will get the data needed to connect to the server
     * and then it will call the connect function in the backend.
     */

    auto hwnd = getInstance_main_window(); // Get the main window handle
    
    // Get the current server name and port number
    update_connection_status_box(hwnd, "Connecting...");

    std::string serverName = get_current_server_name();
    std::string portNumber = get_current_port_number();

    MqttErrorCode err;

    err = MqttManager::getInstance().set_broker_ip(serverName);
    if (err != MqttErrorCode::SUCCESS) {
        // Handle error, e.g., show a message box
        update_connection_status_box(hwnd, MqttManager::getInstance().get_error_message(err));
        return;
    }

    err = MqttManager::getInstance().set_port_num(portNumber);
    if (err != MqttErrorCode::SUCCESS) {
        // Handle error, e.g., show a message box
        update_connection_status_box(hwnd, MqttManager::getInstance().get_error_message(err));
        return;
    }

    // Set the on connect callback to update the connection status box
    MqttManager::getInstance().register_on_connect_callback([this]() {
        this->on_mqtt_connection();
    });

    // If we reach this point:
    err = MqttManager::getInstance().init();
    if (err != MqttErrorCode::SUCCESS) {
        // Handle error, e.g., show a message box
        update_connection_status_box(hwnd, MqttManager::getInstance().get_error_message(err));
        return;
    }
}

void AppController::setup_monitor_module(const std::string& jigID)
{
    this->jig_wifi_monitor = std::make_unique<JigWifiMonitor>(jigID);
    this->jig_debug_monitor = std::make_unique<JigDebugMonitor>(jigID);

    jig_wifi_monitor->start_monitoring([this](bool connection) {
        this->on_change_wifi_status(connection);
    });

    jig_debug_monitor->set_on_debug_data_callback([this](const std::string& debugData){
        this->on_debug_data_received(debugData);
    });
}

void AppController::on_mqtt_connection(void)
{
    auto hwnd = getInstance_main_window(); // Get the main window handle

    reqHandlerRegistry.register_handler(ACTION_SET, PARAM_ERROR, std::make_unique<SetErrorReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_SET, PARAM_TEST, std::make_unique<SetTestReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_SET, PARAM_CHANNEL, std::make_unique<SetChannelReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_CLEAR, PARAM_ERROR, std::make_unique<ClearErrorReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_CLEAR, PARAM_TEST, std::make_unique<ClearTestReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_CLEAR, PARAM_CHANNEL, std::make_unique<ClearChannelReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_GET, PARAM_ERROR, std::make_unique<GetErrorReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_GET, PARAM_TEST, std::make_unique<GetTestReqHandler>());
    reqHandlerRegistry.register_handler(ACTION_GET, PARAM_CHANNEL, std::make_unique<GetChannelReqHandler>());

    // Setup the monitor modules
    std::string jigId = get_selected_jig_id(getInstance_main_window());
    setup_monitor_module(jigId);

    update_connection_status_box(hwnd, "Connected successfully!");
    connection_established(hwnd);
}

void AppController::on_send_button_pressed(void)
{
    // Get the active window
    auto hwnd = getInstance_main_window();

    // Check if a request is already in progress
    if (this->current_request) {
        write_line_on_req_output_terminal(hwnd, false, "A request is already in progress.");
        return;
    }

    // Now, the send button was pressed and I have to handle it. First: get the typed request
    const std::string& jigId = get_selected_jig_id(hwnd);
    const std::string& reqStr = get_typed_request(hwnd);

    // display it
    write_line_on_req_output_terminal(hwnd, true, reqStr);


    // Parse the typed request
    std::istringstream iss(reqStr);
    std::string action, parameter;
    std::vector<std::string> args;

    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);   
    }

    try
    {
        if(tokens.size() < 2)
        {
            throw std::invalid_argument("Command must contain at least action, parameter, and one value.");
        }
    }
    catch(const std::exception& ex)
    {
        // Handle the error, e.g., show a message box or update the status box
        write_line_on_req_output_terminal(hwnd, false, ex.what());
        // destroy request
        this->current_request.reset();
        return;
    }

    action = tokens[ACTION_SEGMENT];
    parameter = tokens[PARAM_SEGMENT];

    args = std::vector<std::string>(tokens.begin() + VALUE_SEGMENT, tokens.end());

    // Construct the request
    this->current_request = std::make_shared<Request>(jigId, action, parameter, args);

    // Validate the request
    try
    {
        current_request->validate();
    }
    catch(const std::exception& ex)
    {
        // Handle the error, e.g., show a message box or update the status box
        write_line_on_req_output_terminal(hwnd, false, ex.what());
        this->current_request.reset(); // destroy request
        return;
    }
    
    this->current_request->set_on_response_received([this](const std::string& response) {
        this->on_req_response_received(response);
    });

    this->current_request->set_on_response_missed([this]() {
        this->on_response_missed();
    });

    this->current_request->set_on_exec_cmds_finished([this]() {
        this->current_request.reset();
    });

    // Execute the request
    current_request->execute();
}

void AppController::on_req_response_received(const std::string& response)
{
    // sent the one after it - if request existed.
    if (this->current_request)
    {
        write_line_on_req_output_terminal(getInstance_main_window(), false, response);
    }
    else
    {
        // display "No request sent, although received a response"
        write_line_on_req_output_terminal(getInstance_main_window(), false, "No request sent, although received: " + response);
    }
}

void AppController::on_response_missed(void)
{
    // sent the one after it - if request existed.
    if (this->current_request)
    {
        write_line_on_req_output_terminal(getInstance_main_window(), false, "No response received, request terminated.");
        // Copy the request before termination
        std::shared_ptr<Request> cpyReq = this->current_request;
        // Terminate the request, reset the current request
        this->current_request.reset();
    }
}

void AppController::on_change_wifi_status(bool connection)
{
    auto hwnd = getInstance_main_window(); // Get the main window handle
    update_status_color(connection);
    update_jig_wifi_connection_box(hwnd,this->jig_wifi_monitor->get_jig_connection_status());
    update_jig_wifi_network_box(hwnd,this->jig_wifi_monitor->get_jig_network_name());
    update_jig_mac_address_box(hwnd,this->jig_wifi_monitor->get_jig_mac_address());
}

void AppController::on_debug_data_received(const std::string& debugData)
{
    write_on_debug_output_terminal(getInstance_main_window(), debugData);
}

