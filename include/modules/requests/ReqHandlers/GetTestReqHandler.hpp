#ifndef GET_TEST_REQ_HANDLER_HPP
#define GET_TEST_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class GetTestReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    GetTestReqHandler() = default;
    ~GetTestReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* GET_TEST_REQ_HANDLER_HPP */
