#pragma once

#include "includes.hpp"

class registry_persist
{
    public:
        bool installPersistence(const std::string& name, const std::string& path, bool systemWide = false);
        bool removePersistence(const std::string& name);
        bool validatePersistence(const std::string& name);

    private:
        HKEY persistenceType = HKEY_CURRENT_USER;
};