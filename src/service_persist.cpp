#include "service_persist.hpp"

bool service_persist::createService(const std::string& serviceName, const std::string& displayName, const std::string& executablePath)
{
    SC_HANDLE scManager = OpenSCManagerA(
        NULL,                           // local machine
        NULL,                           // default database
        SC_MANAGER_CREATE_SERVICE       // permission
    );

    if (scManager == NULL) {
        std::cout << "Failed to open Service Control Manager\n";
        return false;
    }

    SC_HANDLE service = CreateServiceA(
        scManager,                      
        serviceName.c_str(),
        displayName.c_str(),
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
        SERVICE_ERROR_NORMAL,
        executablePath.c_str(),
        NULL, 
        NULL,
        NULL,
        NULL,
        NULL
    );

    if (service == NULL) {
        DWORD error = GetLastError();

        std::cout << "Failed to create service. Error: " << error << "\n";
        if (error == 1073) {
            std::cout << "Service already exists!\n";
        }

        CloseServiceHandle(scManager);
        return false;
    }

    std::cout << "Service created successfully!\n";

    CloseServiceHandle(service);
    CloseServiceHandle(scManager);
    return true;
}

bool service_persist::startService(const std::string& serviceName)
{
    SC_HANDLE scManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    if (scManager == NULL) {
        return false;
    }

    SC_HANDLE service = OpenServiceA(scManager, serviceName.c_str(), SERVICE_START);
    if (service == NULL) {
        CloseServiceHandle(scManager);
        return false;
    }

    bool success = StartServiceA(service, 0, NULL);

    CloseServiceHandle(service);
    CloseServiceHandle(scManager);
    return success;
}

bool service_persist::stopService(const std::string& serviceName)
{
    SC_HANDLE scManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    SC_HANDLE service = OpenServiceA(scManager, serviceName.c_str(), SERVICE_ALL_ACCESS);
    SERVICE_STATUS serviceStatus;

    bool success = ControlService(service, SERVICE_CONTROL_STOP, &serviceStatus);

    CloseServiceHandle(service);
    CloseServiceHandle(scManager);
    return success;
}

bool service_persist::deleteService(const std::string& serviceName)
{
    SC_HANDLE scManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    if (scManager == NULL) {
        return false;
    }

    SC_HANDLE service = OpenServiceA(scManager, serviceName.c_str(), DELETE | SERVICE_STOP);
    if (service == NULL) {
        CloseServiceHandle(scManager);
        return false;
    }

    SERVICE_STATUS serviceStatus;
    ControlService(service, SERVICE_CONTROL_STOP, &serviceStatus);

    bool success = DeleteService(service);

    CloseServiceHandle(service);
    CloseServiceHandle(scManager);
    return success;
}

bool service_persist::validateService(const std::string& serviceName)
{
    SC_HANDLE scManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    if (scManager == NULL) {
        return false;
    }

    SC_HANDLE service = OpenServiceA(scManager, serviceName.c_str(), SERVICE_QUERY_STATUS);
    bool exists = (service != NULL);

    if (service != NULL) {
        CloseServiceHandle(service);
    }
    CloseServiceHandle(scManager);

    return exists;
}