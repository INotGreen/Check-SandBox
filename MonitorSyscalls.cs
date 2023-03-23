using System;
using System.Runtime.InteropServices;

class Program
{
    static void Main(string[] args)
    {
        IntPtr handle = GetModuleHandle("kernel32.dll");
        IntPtr address = GetProcAddress(handle, "I"+ "s" + "D" + "e" + "b" + "u" + "g" + "g" + "e" + "r" + "P" + "r" + "e" + "s" + "e" + "n" + "t");
        if (address == IntPtr.Zero)
        {
            Console.WriteLine("Sandbox detected");
        }
        else
        {
            Console.WriteLine("Sandbox not detected");
        }
        Console.ReadKey();
    }

    [DllImport("kernel32.dll")]
    static extern IntPtr GetModuleHandle(string lpModuleName);

    [DllImport("kernel32.dll")]
    static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
}


/*使用GetModuleHandle和GetProcAddress函数来检查是否存在IsDebuggerPresent函数。
 * 
 * 如果不存在，那么就说明当前运行在沙箱环境中。
 * 这是因为IsDebuggerPresent函数是一个用于检测调试器的系统函数，而在沙箱环境中通常不允许使用调试器。*/