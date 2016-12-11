#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
        int s[2];
        int w;
        char *string = "This is a test string";
        pid_t pid;

        if (socketpair(AF_UNIX, SOCK_STREAM, 0, s) == -1) {
                printf("create unnamed socket pair failed: %s\n", strerror(errno));
                exit(-1);
        }

	printf("sockpair: s[0]: %d, s[1]: %d.\n", s[0], s[1]);

        if ((pid = fork()) > 0) {
                printf("parent process's pid is %d\n", getpid());
        } else if (pid == 0) {
                printf("fork child process successed\n");
                printf("child process's pid is: %d\n", getpid());
		printf("to fork test process!\n");

		char s0[4], s1[4];
		sprintf(s0, "%d", s[0]);
		sprintf(s1, "%d", s[1]);

		if ((pid = fork()) == 0) {
			printf("s0: %s, s1: %s\n", s0, s1);
			execl("/home/huihui/socketpair/test.out", "test.out", s0,
				s1, (char *)NULL);
			perror("execl() failure!\n");
		}
		printf("sockpair: s[0]: %d, s[1]: %d.\n", s[0], s[1]);
                close(s[1]);
                if ((w = write(s[0], string, strlen(string))) == -1) {
                        printf("write socket error: %s\n", strerror(errno));
                        exit(-1);
                }
        } else {
                printf("fork failed: %s\n", strerror(errno));
                exit(-1);
        }
	printf("to forever loop!\n");
        for(;;);
}
