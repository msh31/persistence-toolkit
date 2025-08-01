#pragma once

#include "includes.hpp"

class registry_persist
{
    public:
        bool installPersistence(const std::string& name, const std::string& path, bool systemWide = false);
        bool removePersistence(const std::string& name, bool systemWide = false);
        bool validatePersistence(const std::string& name, bool systemWide = false);
};