#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    // 记录起始时间戳
    ULONGLONG startTime = GetTickCount64();

    // 循环调用 sleep 和 beep 函数实现延时执行
    for (int i = 0; i < 10; i++) {
        Sleep(1000); // 延时1秒
        Beep(10, 500); // 播放10Hz的声音，持续500毫秒
    }

    // 记录结束时间戳
    ULONGLONG endTime = GetTickCount64();

    // 计算程序执行的时间
    ULONGLONG elapsedTime = endTime - startTime;

    // 计算延时执行的时间
    ULONGLONG delayTime = 10 * (1000 + 500);

    // 如果程序执行的时间比延时执行的时间还要短，说明API被hook了，程序处于沙箱环境中，退出程序
    if (elapsedTime < delayTime) {
        cout << "API is hooked, the program is running in sandbox environment." << endl;
        return 0;
    }

    cout << "The program is running normally." << endl;
    return 0;
}

/*使用GetTickCount64记录首个时间戳，记录起始执行程序的时间；
多次循环调用sleep 函数 和 beep 函数 实现 延时执行；
再一次调用GetTickCount64记录时间戳，并比较。
如果 GetTickCount64[2] - GetTickCount64[1] 的时间少于sleep与beep延时调用的时间，说明程序的sleep 或者 beep的API被hook,判定程序处于沙箱环境中，则退出程序；*/
