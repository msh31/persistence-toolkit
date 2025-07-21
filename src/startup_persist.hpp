#pragma once

#include "includes.hpp"

class startup_persist
{
    public:
        bool installStartup(const std::string& targetName, const std::string& location); // location takes either system or user for the startup ppath determiniation
        bool removeStartup(const std::string& targetName);

    private:
        std::string startupPath;

        std::string GetEnv(const char* varName);
        std::string getCurrentExecutablePath();
};