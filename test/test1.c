#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int fd;
    pid_t pid;
    char buf[1024];
    int i;

    // 创建或打开文件data
    if ((fd = open("data", O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1) {
        perror("open");
        exit(1);
    }

    // 创建子进程
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // 子进程写入奇数
        for (i = 1; i <= 999; i += 2) {
            snprintf(buf, sizeof(buf), "%d\n", i);
            write(fd, buf, strlen(buf));
        }
    } else {
        // 父进程写入偶数
        for (i = 0; i <= 998; i += 2) {
            snprintf(buf, sizeof(buf), "%d\n", i);
            write(fd, buf, strlen(buf));
        }
        // 等待子进程结束
        wait(NULL);
    }

    // 关闭文件
    close(fd);

    return 0;
}
