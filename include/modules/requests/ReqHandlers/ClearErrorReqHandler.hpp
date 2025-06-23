#ifndef CLEAR_ERROR_REQ_HANDLER_HPP
#define CLEAR_ERROR_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class ClearErrorReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    ClearErrorReqHandler() = default;
    ~ClearErrorReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};
#endif /* CLEAR_ERROR_REQ_HANDLER_HPP */
