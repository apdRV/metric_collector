#pragma once
#include <string>

class IMetric {
public:
    virtual std::string name() const = 0;
    virtual std::string value_as_string() const = 0;
    virtual ~IMetric() = default;
}; 