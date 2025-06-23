#ifndef I_REQUEST_HANDLER_HPP
#define I_REQUEST_HANDLER_HPP

#include <string>
#include <queue>
#include "ArgValidationResult.hpp"

class IRequestObjects
{
protected:
    std::queue<std::string> exec_cmds; // Commands to be executed by the request handler
    bool is_executing = false; // Flag to indicate if the request is currently executing   

public:
    
    virtual ~IRequestObjects() = default;
};

class IRequestHandler {
public:
    virtual ~IRequestHandler() = default;

    // Checks for the arguments, that they are passed in correct form and range according to the
    // request calling it.
    virtual ArgValidationResult validateArgs(const std::vector<std::string>& args) = 0;

    virtual const std::string prepareCommand(void) = 0;

    // This function is called to check if the request ended execution all it's commands.
    // It is used to know if the request can be destroyed or not.
    // If it returns true, then the request can be destroyed.
    // If it returns false, then the request is still executing and should not be destroyed.
    virtual bool reqExecEnded(void) = 0;
};

#endif /* I_REQUEST_HANDLER_HPP */
