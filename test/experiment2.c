#include "types.h"
#include "user.h"

int main()
{
    int pid;

    // 创建子进程
    pid = fork();

    if (pid < 0) {
        // fork()失败
        printf(2, "fork failed\n");
        exit();
    } else if (pid == 0) {
        // 子进程
        printf(1, "来自子进程的哈囖！");
        exit();
    } else {
        // 父进程
        printf(1, "来自父进程的哈囖！\n");
        // 等待子进程结束
        wait();
        printf(1, "您儿子进程执行完成啦！\n");
    }

    exit();
}
