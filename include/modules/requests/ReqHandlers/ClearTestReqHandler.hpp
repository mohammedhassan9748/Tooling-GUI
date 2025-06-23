#ifndef CLEAR_TEST_REQ_HANDLER_HPP
#define CLEAR_TEST_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class ClearTestReqHandler : public IRequestHandler, public IRequestObjects
{
private:

public:
    ClearTestReqHandler() = default;
    ~ClearTestReqHandler() override = default;

    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* CLEAR_TEST_REQ_HANDLER_HPP */
