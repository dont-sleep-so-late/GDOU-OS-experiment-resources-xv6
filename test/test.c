#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "sem.h"

void myitoa(int i, char* result)
{
	char str[10];
	int pos;
	str[pos = 9] = '\0';
	do {
		str[--pos] = i % 10 + '0';
		i /= 10;
	} while (i);
	strcpy(result, &str[pos]);
}
int main(int argc, char* argv[])
{
	int sd1 = sem_init("sem1", 1); 
	int sd2 = sem_init("sem2", 0);

	int fd = open("data", O_RDWR | O_CREATE);
	
	if (fork() == 0) {
		int i;
		for (i = 1; i < 1000; i += 2) {
			char str[100];
			myitoa(i, str);
			P(sd2);
			write(fd, str, strlen(str));
			write(fd, "\n", 1);
			printf(1, "child wrote %d\n", i);
			V(sd1);
		}
	}
	else {
		int i;
		for (i = 0; i < 1000; i += 2) {
			char str[100];
			myitoa(i, str);
			P(sd1);
			write(fd, str, strlen(str));
			write(fd, "\n", 1);
			printf(1, "parent wrote %d\n", i);
			V(sd2);
		}
		wait();
	} 
	close(fd);
	exit();
}
