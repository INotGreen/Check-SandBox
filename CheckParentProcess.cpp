#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

bool CheckParentProcess()
{
    // 获取当前进程的父进程ID
    DWORD parentPID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
    if (Process32First(hSnapshot, &pe32))
    {
        do {
            if (pe32.th32ProcessID == GetCurrentProcessId())
            {
                parentPID = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    CloseHandle(hSnapshot);

    // 检查父进程是否为沙箱进程
    if (parentPID == 0)
        return false;

    HANDLE hParentProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, parentPID);
    if (hParentProcess == NULL)
        return false;

    std::wstring parentName(MAX_PATH, L'\0');
    DWORD len = GetProcessImageFileNameW(hParentProcess, &parentName[0], MAX_PATH);
    parentName.resize(len);

    bool isSandbox = false;

    // 以下示例代码用于检测VMware、VirtualBox等虚拟机软件的特征
    if (parentName.find(L"vmware") != std::wstring::npos ||
        parentName.find(L"vbox") != std::wstring::npos ||
        parentName.find(L"qemu") != std::wstring::npos ||
        parentName.find(L"vmsrvc") != std::wstring::npos)
    {
        isSandbox = true;
    }

    CloseHandle(hParentProcess);

    return isSandbox;
}

int main()
{
    if (CheckParentProcess())
    {
        std::cout << "Current process is running in sandbox environment." << std::endl;
    }
    else
    {
        std::cout << "Current process is not running in sandbox environment." << std::endl;
    }

    return 0;
}
