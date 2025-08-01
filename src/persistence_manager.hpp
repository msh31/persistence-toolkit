#pragma once
#include "registry_persist.hpp"
#include "startup_persist.hpp" 
#include "service_persist.hpp"

class persistence_manager {
    private:
        registry_persist regPersistence;
        startup_persist startPersistence;
        service_persist servicePersistence;

    public:
        bool installAllPersistence(const std::string& name, const std::string& path);
        bool removeAllPersistence(const std::string& name, const std::string& path);
        bool runComprehensiveTest(const std::string& name, const std::string& path);
};