#include <algorithm>
#include "CmdConfig.hpp"
#include "SetChannelReqHandler.hpp"

ArgValidationResult SetChannelReqHandler::validateArgs(const std::vector<std::string> &args)
{
    if (args.empty())
        return ArgValidationResult(Status::EMPTY_ARGS);

    for (size_t i = 0; i < args.size(); i += 3)
    {        
        // check if the channel number is provided
        if (i >= args.size())
            return ArgValidationResult(Status::INVALID_FORMAT, "Channel number is missing");
        // check if the min and max values are provided
        if (i + 1 >= args.size())
            return ArgValidationResult(Status::INVALID_FORMAT, "Channel min value is missing");
        if (i + 2 >= args.size())
            return ArgValidationResult(Status::INVALID_FORMAT, "Channel max value is missing");

        // check if the arguments are numeric
        if (!std::all_of(args[i].begin(), args[i].end(), ::isdigit))
            return ArgValidationResult(Status::NON_NUMERIC_ARG, args[i]);
        if (!std::all_of(args[i + 1].begin(), args[i + 1].end(), ::isdigit))
            return ArgValidationResult(Status::NON_NUMERIC_ARG, args[i + 1]);
        if (!std::all_of(args[i + 2].begin(), args[i + 2].end(), ::isdigit))
            return ArgValidationResult(Status::NON_NUMERIC_ARG, args[i + 2]);

        unsigned int channel_num = std::stoul(args[i]);
        unsigned int min_value = std::stoul(args[i + 1]);
        unsigned int max_value = std::stoul(args[i + 2]);

        if (channel_num < MIN_CHANNEL_VALUE || channel_num > MAX_CHANNEL_VALUE)
            return ArgValidationResult(Status::OUT_OF_RANGE, args[i]);
        if (min_value < MIN_CHANNEL_RANGE_VALUE || min_value > MAX_CHANNEL_RANGE_VALUE)
            return ArgValidationResult(Status::OUT_OF_RANGE, args[i + 1]);
        if (max_value < MIN_CHANNEL_RANGE_VALUE || max_value > MAX_CHANNEL_RANGE_VALUE)
            return ArgValidationResult(Status::OUT_OF_RANGE, args[i + 2]);
    }

    // Clear previous commands
    while(!this->exec_cmds.empty()){
        this->exec_cmds.pop();
    }

    // Prepare the commands
    for (size_t i = 0; i < args.size(); i += 3)
    {
        std::string cmd = std::string(AT_CMD_SET_CHANNEL) + args[i] + AT_CMD_EQUAL +
                          args[i + 1] + AT_CMD_DASH + args[i + 2] + AT_CMD_CARRIAGE_RETURN;
        exec_cmds.push(cmd);
    }
    
    this->is_executing = true;
    
    return ArgValidationResult(Status::OK);
}

const std::string SetChannelReqHandler::prepareCommand(void)
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

bool SetChannelReqHandler::reqExecEnded(void)
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