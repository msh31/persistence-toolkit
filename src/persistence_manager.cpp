#include "persistence_manager.hpp"

registry_persist regPersistence;
startup_persist startPersistence;
service_persist servicePersistence;

bool persistence_manager::installAllPersistence(const std::string& name, const std::string& path)
{
	bool allInstalled = true;
	allInstalled &= regPersistence.installPersistence(name, path, false);
	allInstalled &= regPersistence.installPersistence(name, path, true);
	allInstalled &= startPersistence.installStartup(name);
	allInstalled &= servicePersistence.createService(name, name, path);

	return allInstalled;
}

bool persistence_manager::removeAllPersistence(const std::string& name, const std::string& path)
{
	bool allRemoved = true;
	allRemoved &= regPersistence.removePersistence(name, false);//user
	allRemoved &= regPersistence.removePersistence(name, true);//system
	allRemoved &= startPersistence.removeStartup(name);
	allRemoved &= servicePersistence.deleteService(name);

	return allRemoved;
}

bool persistence_manager::runComprehensiveTest(const std::string& name, const std::string& path)
{
    std::cout << "=== COMPREHENSIVE PERSISTENCE TEST ===\n\n";

    std::cout << "Installing all persistence methods...\n";
    if (!installAllPersistence(name, path)) {
        std::cout << "Installation failed!\n";
        return false;
    }
    std::cout << "All persistence methods installed!\n\n";

    std::cout << "Validating persistence...\n";
    bool userReg = regPersistence.validatePersistence(name, false);
    bool systemReg = regPersistence.validatePersistence(name, true);
    bool service = servicePersistence.validateService(name);

    // compact if statements; condition ? true : false
    std::cout << "User Registry: " << (userReg ? "Valid" : "Failed") << "\n";
    std::cout << "System Registry: " << (systemReg ? "Valid" : "Failed") << "\n";
    std::cout << "Service: " << (service ? "Valid" : "Failed") << "\n\n";

    std::cout << "Cleaning up...\n";
    removeAllPersistence(name, path);
    std::cout << "Cleanup complete!\n";

    return userReg && systemReg && service;
}