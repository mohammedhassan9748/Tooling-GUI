#ifndef SET_ERROR_REQ_HANDLER_HPP
#define SET_ERROR_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class SetErrorReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    SetErrorReqHandler() = default;
    ~SetErrorReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* SET_ERROR_REQ_HANDLER_HPP */
