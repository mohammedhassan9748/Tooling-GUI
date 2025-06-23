#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <memory>
#include <mutex>
#include <functional>
#include <unordered_map>
#include <condition_variable>
#include <atomic>
#include <thread>


#include "CmdConfig.hpp"
#include "IRequestHandler.hpp"
#include "RequestHandlerRegistry.hpp"

class Request
{
private:

	const std::string req_topic;
	const std::string resp_topic;

	const std::string& jigId;
	const std::string& action;
	const std::string& parameter;
	const std::vector<std::string>& args;
	
	std::function<void(const std::string&)> onResponseReceived = nullptr;
	std::function<void()> onExecCmdsFinished = nullptr;	

	IRequestHandler *reqHandler = nullptr;

	std::mutex exec_mtx;
	std::condition_variable exec_cv;
	bool resp_received = false;

	void handle_message(const std::string& response);
	void start_monitoring_one_cmd(void);
	void monitoring_one_cmd_loop(void);

public:

	// RAII(Resource Acquisition Is Initialization): Rule(0)
	Request() = delete; // Delete default constructor
	// copy constructor
	Request(const Request&) = delete;
	// move constructor
	Request(Request&&) = delete;
	// copy assignment operator
	Request& operator=(const Request&) = delete;
	// move assignment operator
	Request& operator=(Request&&) = delete;
	// destructor
	~Request() = default;

	// Parameterized constructor 1
	Request(const std::string& jigId,
			const std::string& action,
			const std::string& parameter,
			const std::vector<std::string>& args
	);

	void validate(void);

	void execute(void);

	void set_on_response_received(std::function<void(const std::string&)> callback);

	void set_on_exec_cmds_finished(std::function<void()> callback);
};

#endif // REQUEST_HPP
