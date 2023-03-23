#include <iostream>
#include <string>
#include <intrin.h>
#include <Windows.h>

bool detect_vt_x_amd_v() {
    int cpu_info[4] = { -1 };
    __cpuid(cpu_info, 1);

    // Check Intel VT-x or AMD-V support
    return (cpu_info[2] & (1 << 5)) || (cpu_info[2] & (1 << 2));
}

bool detect_vmware() {
    const char* vmware_str = "VMwareVMware";
    const size_t vmware_str_len = strlen(vmware_str);
    unsigned char mem[64] = { 0 };

    for (size_t i = 0; i < sizeof(mem) - vmware_str_len; ++i) {
        if (memcmp(mem + i, vmware_str, vmware_str_len) == 0) {
            return true;
        }
    }

    return false;
}

bool detect_virtualbox() {
    HKEY h_key;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\Description\\System", 0, KEY_READ, &h_key) != ERROR_SUCCESS) {
        return false;
    }

    char value[256] = { 0 };
    DWORD value_size = sizeof(value);
    if (RegQueryValueExA(h_key, "SystemBiosVersion", NULL, NULL, (LPBYTE)value, &value_size) != ERROR_SUCCESS) {
        RegCloseKey(h_key);
        return false;
    }

    RegCloseKey(h_key);
    return strstr(value, "VBOX") != nullptr;
}

int main() {
    if (detect_vt_x_amd_v()) {
        std::cout << "Intel VT-x or AMD-V virtualization technology detected." << std::endl;
    } else {
        std::cout << "Intel VT-x or AMD-V virtualization technology not detected." << std::endl;
    }

    if (detect_vmware()) {
        std::cout << "VMware detected." << std::endl;
    } else {
        std::cout << "VMware not detected." << std::endl;
    }

    if (detect_virtualbox()) {
        std::cout << "VirtualBox detected." << std::endl;
    } else {
        std::cout << "VirtualBox not detected." << std::endl;
    }

    return 0;
}
