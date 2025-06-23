#ifndef SET_TEST_REQ_HANDLER_HPP
#define SET_TEST_REQ_HANDLER_HPP

#include "IRequestHandler.hpp"

class SetTestReqHandler : public IRequestHandler, public IRequestObjects
{

private:

public:
    SetTestReqHandler() = default;
    ~SetTestReqHandler() override = default;
    
    ArgValidationResult validateArgs(const std::vector<std::string>& args) override;

    const std::string prepareCommand(void) override;

    bool reqExecEnded(void) override;
};

#endif /* SET_TEST_REQ_HANDLER_HPP */
