# 🔄 Persistence Toolkit - Educational Malware Sample

**Part of the [Malware Analysis Learning Course](https://github.com/msh31/malware-analysis) - Challenge 2A**

Educational demonstration of Windows persistence mechanisms used by malware to maintain access across system reboots and user sessions.

## ⚠️ Educational Purpose Only

This code demonstrates persistence techniques for cybersecurity education in controlled environments.

## 🎯 Learning Objectives

This project teaches core malware persistence techniques used by 90% of threats:

### **Registry Persistence**
- **User-level Run keys** - `HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run`
- **System-level Run keys** - `HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run` 
- **RunOnce variants** - Self-deleting persistence for single execution

### **Startup Folder Persistence**
- **User startup folder** - File placement in user-specific startup directories
- **System startup folder** - All users startup folder targeting
- **Legitimate process mimicry** - Disguising malicious executables

### **Service Persistence**
- **Windows service creation** - Background persistence with system privileges
- **Service configuration** - Automatic startup and failure recovery
- **Service management** - Installation, validation, and removal

## 🛠️ Compilation & Usage

### **Requirements**
- **Platform:** Windows 10/11
- **Compiler:** Visual Studio 2022 or MinGW-w64
- **Dependencies:** Windows API (advapi32.lib for registry and service operations)

### **Build Instructions**

**Visual Studio 2022:**
```bash
start persistence-toolkit.sln

Build → Configuration Manager → Release → Build Solution
```

### **Safe Execution**
```bash
./persistence-toolkit.exe

# Verify persistence installation
# Check registry, startup folders, or services as appropriate
```

## 📊 Sample Output

```
=== REGISTRY PERSISTENCE TEST ===
✅ Persistence installed successfully!
Entry: TestPersistence -> C:\Windows\System32\notepad.exe
✅ Persistence validated - entry exists!

=== TESTING REMOVAL ===
✅ Persistence removed successfully!
✅ Removal validated - entry no longer exists!

=== STARTUP FOLDER PERSISTENCE ===
✅ Executable copied to startup folder
✅ Persistence will activate on next user login

=== SERVICE PERSISTENCE ===
✅ Windows service created successfully
✅ Service configured for automatic startup
✅ Background persistence established
```

## 🔬 Malware Analysis Value

### **Real-World Applications**
These persistence techniques appear in major malware families:
- **Ryuk ransomware** - Registry Run key persistence
- **APT groups** (APT39, APT41, FIN7) - Multi-vector persistence strategies
- **Banking trojans** (Mekotio, Saigon) - Startup folder and service persistence
- **Advanced threats** - Combined registry, file, and service-based persistence

### **Blue Team Learning**
- **Persistence detection** - Registry monitoring, file system changes, service creation
- **Incident response** - Comprehensive persistence removal strategies  
- **Threat hunting** - Behavioral signatures for persistence installation
- **System hardening** - Prevention and detection improvements

---

## 📖 References & Further Reading

- **[MITRE ATT&CK: Registry Run Keys / Startup Folder](https://attack.mitre.org/techniques/T1547/001/)**
- **[MITRE ATT&CK: Windows Service](https://attack.mitre.org/techniques/T1543/003/)**
- **[Windows Registry Reference](https://docs.microsoft.com/en-us/windows/win32/sysinfo/registry)**
- **[Service Control Manager](https://docs.microsoft.com/en-us/windows/win32/services/service-control-manager)**