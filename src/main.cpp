#include "registry_persist.hpp"
#include "startup_persist.hpp"
#include "service_persist.hpp"
#include "persistence_manager.hpp"

int main()
{
    persistence_manager persistenceManager;
    persistenceManager.runComprehensiveTest("Malware", "C:\\malware.exe");

    return 0;
}