#ifndef SET_CHANNEL_REQ_HANDLER_HPP
#define SET_CHANNEL_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class SetChannelReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    SetChannelReqHandler() = default;
    ~SetChannelReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* SET_CHANNEL_REQ_HANDLER_HPP */
