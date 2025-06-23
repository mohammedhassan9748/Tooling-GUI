#ifndef GET_ERROR_REQ_HANDLER_HPP
#define GET_ERROR_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class GetErrorReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    GetErrorReqHandler() = default;
    ~GetErrorReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* GET_ERROR_REQ_HANDLER_HPP */
