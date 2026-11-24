#pragma once
#include "tractor.h"
class ValidationException {
private:
    std::string msg;
public:
    ValidationException(const std::string& msg) : msg(msg) {}
    const std::string& getMsg() const { return msg; }
};

class Validator {
public:
    void validate(Tractor& t) const;
};