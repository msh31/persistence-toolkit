#pragma once

#include "includes.hpp"

class startup_persist
{
    public:
        bool installStartup(const std::string& targetName, bool systemWide = false);
        bool removeStartup(const std::string& targetName);

    private:
        std::string startupPath;

        std::string GetEnv(const char* varName);
        std::string getCurrentExecutablePath();
};