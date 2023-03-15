
#include <Windows.h>
#include <stdio.h>
// 调用Beep 实现延迟执行
int time_Beep()
{
    // 设置延迟 300000毫秒 5分钟
    int wh_compter = 0;
    int wh_total = 300000;

    while (wh_compter < wh_total)
    {
        Beep(2, 1); // 2hertz, 1ms 设置低频和短暂的间隔时间实现听不见蜂鸣声
        wh_compter++;
    }

    if (wh_compter > wh_total - 1)
        return 1;

    return 0;
}

int main()
{
    if (time_Beep())
        printf("调用Beep 延迟执行成功 \n");
    else
        printf("调用Beep 延迟执行失败 \n!");

    return 0;
}