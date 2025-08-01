#pragma once

#include "includes.hpp"

class service_persist
{
    public:
        bool createService(const std::string& serviceName, const std::string& displayName, const std::string& executablePath);
        bool startService(const std::string& serviceName);
        bool stopService(const std::string& serviceName);
        bool deleteService(const std::string& serviceName);
        bool validateService(const std::string& serviceName);
};