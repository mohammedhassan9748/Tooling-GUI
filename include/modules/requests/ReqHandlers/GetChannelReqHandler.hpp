#ifndef GET_CHANNEL_REQ_HANDLER_HPP
#define GET_CHANNEL_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class GetChannelReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    GetChannelReqHandler() = default;
    ~GetChannelReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* GET_CHANNEL_REQ_HANDLER_HPP */
