#ifndef ARG_VALIDATION_RESULT_HPP
#define ARG_VALIDATION_RESULT_HPP

#include <string>

enum class Status
{
    OK,
    EMPTY_ARGS,
    NON_NUMERIC_ARG,
    OUT_OF_RANGE,
    INVALID_FORMAT,
    UNKNOWN_ERROR
};

class ArgValidationResult
{
private:
    std::string reason_;
    Status status_;

    // Delete the default constructor to prevent instantiation without parameters
    ArgValidationResult() = delete;

public:
    ArgValidationResult(const ArgValidationResult &) = default;
    ArgValidationResult &operator=(const ArgValidationResult &) = default;

    ArgValidationResult(ArgValidationResult &&) = default;
    ArgValidationResult &operator=(ArgValidationResult &&) = default;

    // destructor
    ~ArgValidationResult() = default;

    ArgValidationResult(Status status, const std::string &reason);

    ArgValidationResult(Status status);

    Status getStatus() const;
    std::string getReason() const;

    std::string to_string(void) const;
};

#endif // !ARG_VALIDATION_RESULT_HPP
