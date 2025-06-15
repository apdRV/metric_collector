#pragma once
#include "IMetric.h"
#include <string>
#include <sstream>

template<typename T>
class Metric : public IMetric {
    std::string m_name;
    T m_value;
public:
    Metric(const std::string& name, T value) : m_name(name), m_value(value) {}
    std::string name() const override { return m_name; }
    std::string value_as_string() const override {
        std::ostringstream oss;
        oss << m_value;
        return oss.str();
    }
}; 