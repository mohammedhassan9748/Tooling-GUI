#include "Request.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <exception>
#include "CmdConfig.hpp"
#include "mqtt_manager.hpp"
#include "RequestHandlerRegistry.hpp"
#include "SetChannelReqHandler.hpp"
#include "SetErrorReqHandler.hpp"
#include "SetTestReqHandler.hpp"
#include "ClearChannelReqHandler.hpp"
#include "ClearErrorReqHandler.hpp"
#include "ClearTestReqHandler.hpp"
#include "GetChannelReqHandler.hpp"
#include "GetErrorReqHandler.hpp"
#include "GetTestReqHandler.hpp"


/** ===================================================================================== //
 *  ====================================Private Methods================================== //
 * ====================================================================================== */
void Request::handle_message(const std::string& response)
{
    // Process the response message
    if (this->onResponseReceived) {
        // 
        this->onResponseReceived(response);
    }

    if(this->reqHandler->reqExecEnded() && this->onExecCmdsFinished) {
        this->onExecCmdsFinished();
    }
    else
    {
        // If the request is not finished, execute the next command
        this->execute();
    }
}

void Request::start_monitoring_one_cmd(void)
{
    // Start a thread to monitor the command execution
    std::unique_lock<std::mutex> lock(this->exec_mtx);
    
    bool timeout = !this->exec_cv.wait_for(lock, std::chrono::seconds(5), [this]() { return ; });
    
    if(timeout)
    {
        // If timeout occurs, we can handle it here
        std::cerr << "Command execution timed out." << std::endl;
        // You can also throw an exception or handle it as needed
        break; // Exit the loop if you want to stop monitoring
    }

}

/** ===================================================================================== //
 *  ====================================Public Methods=================================== //
 * ====================================================================================== */

Request::Request(const std::string &jigId,
                 const std::string &action,
                 const std::string &parameter,
                 const std::vector<std::string> &args)
: jigId(jigId), action(action), parameter(parameter), args(args), req_topic(jigId + "/" + JIG_REQ_TOPIC),
    resp_topic(jigId + "/" + JIG_RESP_TOPIC)
{

    // Get the request handler for the action and parameter
    this->reqHandler = RequestHandlerRegistry::getInstance().get_request_handler(this->action, this->parameter);
    
    // subscribe to the response topic
    MqttManager::getInstance().register_on_message_callback(
        this->resp_topic,
        [this](const std::string &message) {
            this->handle_message(message);
        }
    );
}

void Request::set_on_response_received(std::function<void(const std::string &)> callback)
{
    this->onResponseReceived = std::move(callback);
}

void Request::set_on_exec_cmds_finished(std::function<void()> callback)
{
    this->onExecCmdsFinished = std::move(callback);
}

void Request::validate(void)
{
    // Check if this command never existed
    if (reqHandler == nullptr)
    {
        throw std::runtime_error("Request handler not found for action: " + this->action + ", parameter: " + this->parameter);
    }

    // Last: check for the values given if they are in range
    if (this->action.empty() || this->parameter.empty())
    {
        throw std::invalid_argument("Action or parameter cannot be empty.");
    }

    if (this->reqHandler == nullptr)
    {
        throw std::invalid_argument("Invalid action or parameter: " + this->action + ", " + this->parameter);
    }

    // Validate the arguments using the request handler
    ArgValidationResult result = reqHandler->validateArgs(this->args);
    if (result.getStatus() != Status::OK)
    {
        throw std::invalid_argument(result.to_string());
    }
}

void Request::execute(void)
{
    const std::string currCmd = this->reqHandler->prepareCommand();
    if(!currCmd.empty())
    {
        // start monitoring the command execution
        if(this->)
        MqttManager::getInstance().publish(this->req_topic, currCmd, 1, false);
    }
}

