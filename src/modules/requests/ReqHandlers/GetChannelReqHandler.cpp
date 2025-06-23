#include <algorithm>
#include "CmdConfig.hpp"
#include "GetChannelReqHandler.hpp"

ArgValidationResult GetChannelReqHandler::validateArgs(const std::vector<std::string> &args)
{
    if (args.empty())
        return ArgValidationResult(Status::EMPTY_ARGS);

    for (const auto &arg : args)
    {
        if (!std::all_of(arg.begin(), arg.end(), ::isdigit))
            return ArgValidationResult(Status::NON_NUMERIC_ARG, arg);

        unsigned int value = std::stoul(arg);
        if (value < MIN_CHANNEL_VALUE || value > MAX_CHANNEL_VALUE)
            return ArgValidationResult(Status::OUT_OF_RANGE, arg);
    }

    // Clear previous commands
    while(!this->exec_cmds.empty())
    {
        this->exec_cmds.pop();
    }

    // Prepare the commands
    for (const auto &arg : args)
    {
        std::string cmd = std::string(AT_CMD_GET_CHANNEL) + arg + AT_CMD_CARRIAGE_RETURN;
        exec_cmds.push(cmd);
    }

    this->is_executing = true;

    return ArgValidationResult(Status::OK);
}

const std::string GetChannelReqHandler::prepareCommand(void)
{
    if (this->exec_cmds.empty())
    {
        return ""; // No commands to send
    }

    // save the current command to be executed
    std::string current_cmd = this->exec_cmds.front();
    this->exec_cmds.pop();

    return current_cmd;
}

bool GetChannelReqHandler::reqExecEnded(void)
{
    if (this->exec_cmds.empty())
    {
        this->is_executing = false;
    }
    else
    {
        this->is_executing = true;
    }
    
    return !this->is_executing;
}