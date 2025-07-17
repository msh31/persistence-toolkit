#include "registry_persist.hpp"

int main()
{
    registry_persist regPersist;

    std::cout << "=== REGISTRY PERSISTENCE TEST ===\n\n";

    std::string programName = "TestPersistence";
    std::string programPath = "C:\\Windows\\System32\\notepad.exe";

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

    std::cout << "\n=== TESTING REMOVAL ===\n";
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

    return 0;
}