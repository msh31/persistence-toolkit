#include "registry_persist.hpp"

bool registry_persist::installPersistence(const std::string& name, const std::string& path, bool systemWide)
{
	HKEY key;
	DWORD type;
	HKEY targetHive;

	if (systemWide) {
		targetHive = HKEY_LOCAL_MACHINE;
	}
	else {
		targetHive = HKEY_CURRENT_USER;
	}

	if (RegOpenKeyExA(targetHive, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &key) == ERROR_SUCCESS) {
		if (RegSetValueExA(key, name.c_str(), 0, REG_SZ, (LPBYTE)path.c_str(), path.length() + 1) == ERROR_SUCCESS) {
			RegCloseKey(key);
			return true;
		}
		RegCloseKey(key);
	}

	return false;
}

bool registry_persist::removePersistence(const std::string& name, bool systemWide)
{
	HKEY key;
	HKEY targetHive;

	if (systemWide) {
		targetHive = HKEY_LOCAL_MACHINE;
	}
	else {
		targetHive = HKEY_CURRENT_USER;
	}

	if (RegOpenKeyExA(targetHive, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &key) == ERROR_SUCCESS) {
		if (RegDeleteValueA(key, name.c_str()) == ERROR_SUCCESS) {
			RegCloseKey(key);
			return true;
		}
		RegCloseKey(key);
	}

	return false;
}

bool registry_persist::validatePersistence(const std::string& name, bool systemWide)
{
	HKEY key;
	char buffer[512];
	DWORD dataSize = sizeof(buffer);
	DWORD type;
	HKEY targetHive;

	if (systemWide) {
		targetHive = HKEY_LOCAL_MACHINE;
		std::cout << "Validating system registry (HKLM)...\n";
	}
	else {
		targetHive = HKEY_CURRENT_USER;
		std::cout << "Validating user registry (HKCU)...\n";
	}

	LONG result = RegOpenKeyExA(targetHive, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &key);
	if (result == ERROR_SUCCESS) {
		LONG queryResult = RegQueryValueExA(key, name.c_str(), nullptr, &type, (LPBYTE)buffer, &dataSize);
		if (queryResult == ERROR_SUCCESS) {
			std::cout << "Found registry entry: " << buffer << "\n";
			RegCloseKey(key);
			return true;
		}
		else {
			std::cout << "Registry entry not found. Error: " << queryResult << "\n";
		}
		RegCloseKey(key);
	}
	else {
		std::cout << "Failed to open registry for validation. Error: " << result << "\n";
	}

	return false;
}