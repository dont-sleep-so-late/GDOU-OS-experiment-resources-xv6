#include "types.h"
#include "user.h"
#include "fcntl.h"

void myitoa(int i, char* result)
{
	char str[5];
	int pos;
	str[pos = 4] = '\0';
	do {
		str[--pos] = i % 10 + '0';
		i /= 10;
	} while (i);
	strcpy(result, &str[pos]);
}

int main()
{
    int pid;
    char str[100];
    int fd = open("data", O_RDWR | O_CREATE);
    // 创建子进程
    pid = fork();

    if (pid < 0) {
        // fork()失败
        printf(2, "fork failed\n");
        exit();
    } else if (pid == 0) {
        // 子进程
        int i;
	for (i = 1; i < 1000; i += 2) {
		myitoa(i, str);
		P(sem2);
                write(fd, str, strlen(str));
                write(fd, "\n", 1);
		printf(1, "pid : %d ", pid);
		printf(1, "child wrote %d\n", i);
		V(sem1);
	}
        exit();
    } else {
        // 父进程
	int i;
	for (i = 0; i < 1000; i += 2) {
		myitoa(i, str);
		P(sem1);
                write(fd, str, strlen(str));
                write(fd, "\n", 1);
		printf(1, "pid : %d ", pid);
		printf(1, "parent wrote %d\n", i);
		V(sem2);
	}
        // 等待子进程结束
        wait();

    }
    close(fd);
    exit();
}
