#include "ArgValidationResult.hpp"

ArgValidationResult::ArgValidationResult(Status status, const std::string &reason)
    : status_(status), reason_(reason) {}

ArgValidationResult::ArgValidationResult(Status status)
    : status_(status), reason_("") {}

Status ArgValidationResult::getStatus() const
{
    return status_;
}

std::string ArgValidationResult::getReason() const
{
    return reason_;
}

std::string ArgValidationResult::to_string(void) const
{
    switch (status_)
    {
        case Status::OK:
            return "OK";
        case Status::EMPTY_ARGS:
            return "Empty arguments";
        case Status::NON_NUMERIC_ARG:
            return "Non-numeric argument: " + reason_;
        case Status::OUT_OF_RANGE:
            return "Argument out of range: " + reason_;
        case Status::INVALID_FORMAT:
            return "Invalid format: " + reason_;
        case Status::UNKNOWN_ERROR:
            return "Unknown error";
        default:
            return "Unknown status";
    }
}