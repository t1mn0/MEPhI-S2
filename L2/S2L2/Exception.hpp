#pragma once
#include <string>

#define RESET	"\033[0m"
#define RED		"\033[1;31m"

enum class ErrorCode {
    invalid_argument,
    out_of_range,
    system_error,
    overflow_error,
    empty_container_error,
    insufficient_arguments_error,
    dereference_nullptr
};

class Exception {
private:
    ErrorCode errorCode;

public:
    Exception(ErrorCode ec) : errorCode(ec) {}

    std::string getErrorMessage() const {
        std::string msg_value;
        std::string msg = RED;
        msg += RESET;
        switch (errorCode) {
        case ErrorCode::invalid_argument:
            msg_value = "invalid argument";
            break;
        case ErrorCode::out_of_range:
            msg_value = "out_of_range";
            break;
        case ErrorCode::system_error:
            msg_value = "system_error";
            break;
        case ErrorCode::overflow_error:
            msg_value = "overflow_error";
            break;
        case ErrorCode::empty_container_error:
            msg_value = "empty_container_error";
            break;
        case ErrorCode::insufficient_arguments_error:
            msg_value = "insufficient_arguments_error";
            break;
        case ErrorCode::dereference_nullptr:
            msg_value = "dereference_nullptr";
            break;
        default:
            msg_value = "unknown error";
            break;
        }

        msg.insert(7, msg_value.c_str());

        return msg;
    }
};
