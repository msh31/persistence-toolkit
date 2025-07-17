#pragma once

#include "includes.hpp"

class registry_persist
{
    public:
        bool installUserPersistence(const std::string& name, const std::string& path);
        bool installSystemPersistence(const std::string& name, const std::string& path);
        bool removePersistence(const std::string& name);
        bool validatePersistence(const std::string& name);

    private:
        std::string getUserRunKeyPath();
};