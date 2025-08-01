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
	}
	else {
		targetHive = HKEY_CURRENT_USER;
	}

	if (RegOpenKeyExA(targetHive, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &key) == ERROR_SUCCESS) {
		if (RegQueryValueExA(key, name.c_str(), nullptr, &type, (LPBYTE)buffer, &dataSize) == ERROR_SUCCESS) {
			RegCloseKey(key);
			return true;
		}
		RegCloseKey(key);
	}

	return false;
}