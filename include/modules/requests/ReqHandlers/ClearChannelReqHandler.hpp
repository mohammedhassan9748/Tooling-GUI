#ifndef CLEAR_CHANNEL_REQ_HANDLER_HPP
#define CLEAR_CHANNEL_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class ClearChannelReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    ClearChannelReqHandler() = default;
    ~ClearChannelReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* CLEAR_CHANNEL_REQ_HANDLER_HPP */
